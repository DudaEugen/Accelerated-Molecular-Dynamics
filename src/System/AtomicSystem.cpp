#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <random>
#include "System/AtomicSystem.hpp"
#include "Parallel/MPI/Processes.hpp"

md::AtomicSystem::AtomicSystem(
	const std::vector<Atom>& allAtoms,
	IPotential* atomicPotential,
	AThermostat* thermostat
) : AtomicSystem{allAtoms, std::vector{atomicPotential}, thermostat}
{
}

md::AtomicSystem::AtomicSystem(
	const std::vector<Atom>& allAtoms,
	std::vector<IPotential*> potentials,
	AThermostat* thermostat
) : 
    atoms{allAtoms},
    potentials{potentials},
    neighboursList{
        atoms,
        (*std::min_element(
            potentials.begin(),
            potentials.end(),
            [](const IPotential *a, const IPotential *b){ return a->getCutRadius() < b->getCutRadius(); }
        ))->getCutRadius(),
        1.2 * (*std::min_element(
            potentials.begin(),
            potentials.end(),
            [](const IPotential *a, const IPotential *b){ return a->getCutRadius() < b->getCutRadius(); }
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
    double cutRadius = (*std::min_element(
        potentials.begin(),
        potentials.end(),
        [](const IPotential *a, const IPotential *b){ return a->getCutRadius() < b->getCutRadius(); }
    ))->getCutRadius();
    Vector cellSize = neighboursList.getCellSize();
    double minCellSize = *std::min_element(cellSize.begin(), cellSize.end());

    double timeForNeighboursRefresh = -1;
    for (double currentTime = 0; currentTime < time; currentTime += timeStep)
    {
        if (timeForNeighboursRefresh < 0)
        {
            neighboursList.refresh(atoms);
            double maxVelocity = (*std::max_element(
                atoms.begin(),
                atoms.end(),
                [](const Atom& first, const Atom& second)
                {
                    return first.getVelocity().absoluteValue() < second.getVelocity().absoluteValue();
                }
            )).getVelocity().absoluteValue();
            timeForNeighboursRefresh = (minCellSize - cutRadius) / (2 * maxVelocity);
        }
        timeForNeighboursRefresh -= timeStep;

        std::for_each(atoms.begin(), atoms.end(), [](Atom& atom){ atom.setAcceleration(Vector{}); });
        for (auto potential: potentials)
        {
            potential->computeAndSetAccelerations(neighboursList.getPairs());
        }

        neighboursList.getParallelCellGroups().exchangeAccelerations();

        thermostat->heatExchange(atoms);

        for (auto& atom: atoms)
        {
            atom.move(timeStep);
        }
    }
}

void md::AtomicSystem::setRandomVelocities()
{
    double mass = std::accumulate(
        atoms.begin(), atoms.end(), .0, [](double acc, const Atom& atom){ return acc + atom.mass; }
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
