#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <random>
#include "System/AtomicSystem.hpp"
#include "Parallel/MPI/Processes.hpp"

md::AtomicSystem::AtomicSystem(
	const std::vector<Atom>& allAtoms,
	APotential* atomicPotential,
	AThermostat* thermostat
) : AtomicSystem{allAtoms, std::vector{atomicPotential}, thermostat}
{
}

md::AtomicSystem::AtomicSystem(
	const std::vector<Atom>& allAtoms,
	std::vector<APotential*> potentials,
	AThermostat* thermostat
) : 
    atoms{allAtoms},
    potentials{potentials},
    neighboursList{
        atoms,
        (*std::min_element(
            potentials.cbegin(),
            potentials.cend(),
            [](const APotential *a, const APotential *b){ return a->getCutRadius() < b->getCutRadius(); }
        ))->getCutRadius(),
        1.2 * (*std::min_element(
            potentials.cbegin(),
            potentials.cend(),
            [](const APotential *a, const APotential *b){ return a->getCutRadius() < b->getCutRadius(); }
        ))->getCutRadius()
    },
    thermostat{thermostat}
{
}

md::AtomicSystem::~AtomicSystem()
{
    delete thermostat;
}

void md::AtomicSystem::run(double time, double timeStep)
{
    run(time, timeStep, [](std::uint64_t, const std::vector<Atom>&){});
}

void md::AtomicSystem::run(
    double time,
    double timeStep,
    const std::function<void(std::uint64_t stepIndex, const std::vector<Atom>&)>& watcher
)
{
    double cutRadius = (*std::min_element(
        potentials.cbegin(),
        potentials.cend(),
        [](const APotential *a, const APotential *b){ return a->getCutRadius() < b->getCutRadius(); }
    ))->getCutRadius();
    Vector cellSize = neighboursList.getCellSize();
    double minCellSize = *std::min_element(cellSize.cbegin(), cellSize.cend());

    double maxDistanceForNeighboursRefresh = -1;
    std::uint64_t stepIndex = 0;
    for (double currentTime = 0; currentTime < time; currentTime += timeStep)
    {
        double maxVelocity = (*std::max_element(
            atoms.cbegin(),
            atoms.cend(),
            [](const Atom& first, const Atom& second)
            {
                return first.getVelocity().absoluteValue() < second.getVelocity().absoluteValue();
            }
        )).getVelocity().absoluteValue();
        if (maxDistanceForNeighboursRefresh < 0)
        {
            neighboursList.refresh(atoms);
            maxDistanceForNeighboursRefresh = (minCellSize - cutRadius) / 2;
        }
        else
        {
            neighboursList.updateDistances();
        }
        maxDistanceForNeighboursRefresh -= 2 * maxVelocity * timeStep;

        std::for_each(atoms.begin(), atoms.end(), [](Atom& atom){ atom.setAcceleration(Vector{}); });
        for (auto potential: potentials)
        {
            potential->addAccelerations(neighboursList);
        }

        neighboursList.getParallelCellGroups().exchangeAccelerations();

        thermostat->heatExchange(atoms);

        for (auto& atom: atoms)
        {
            atom.move(timeStep);
        }

        watcher(stepIndex, atoms);
        ++stepIndex;
    }
}

void md::AtomicSystem::setRandomVelocities()
{
    double mass = std::accumulate(
        atoms.cbegin(), atoms.cend(), .0, [](double acc, const Atom& atom){ return acc + atom.mass; }
    ) / atoms.size();
    double standartDeviation = std::sqrt(kBoltzmann * thermostat->getTemperature() / mass);
    auto rand = std::bind( 
		std::normal_distribution<double>(0, standartDeviation), 
		std::mt19937(std::chrono::system_clock::now().time_since_epoch().count())
	);

    for (auto& atom: atoms)
    {
        Vector newVelocity;
        for (auto& projection: newVelocity)
        {
            projection = rand();
        }
        atom.setVelocity(newVelocity);
    }

    Processes processes;
    processes.setVelocities(atoms);
}
