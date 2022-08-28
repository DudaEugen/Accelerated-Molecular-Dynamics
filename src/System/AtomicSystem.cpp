#include <algorithm>
#include "System/AtomicSystem.hpp"

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
        for (auto potential: potentials)
        {
            potential->computeAndSetAccelerations(neighboursList.getPairs());
        }
        // TODO: MPI;
        thermostat->heatExchange(atoms);
        for (auto& atom: atoms)
        {
            atom.move(timeStep);
        }
    }
}
