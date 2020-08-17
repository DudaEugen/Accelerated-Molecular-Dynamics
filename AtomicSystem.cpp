#include "AtomicSystem.h"

AtomicSystem::AtomicSystem(const std::vector<Atom>& allAtoms, APotential* atomicPotential, BorderConditions* borderCond)
: atoms{ allAtoms }, borderConditions{ borderCond }, potential{ atomicPotential }
{
    computeCellSize();
}

void AtomicSystem::computeCellSize()
{
    double reserveCellsNumber = 1;
    double minimumSize = potential->getCutRadius();
    for(projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
    {
        bool isPeriodic = false;
        if (borderConditions != nullptr)
            isPeriodic = borderConditions->getBorderTypes()[i] == BorderConditions::borderType::periodic;

        double systemSize;
        if (isPeriodic)
        {
            systemSize = borderConditions->getSize()[i];
            firstCellPosition[i] = 0;
        }
        else
        {
            const auto minmax = std::minmax_element(atoms.begin(), atoms.end(), 
                [i](const Atom& atom1, const Atom& atom2) { return atom1.getCoordinates()[i] < atom2.getCoordinates()[i]; });
            // to min and max i-th coordinates add reserve minimumSize value, because these coordinates can change in time
            double minCoordinate = minmax.first->getCoordinates()[i] - minimumSize;
            double maxCoordinate = minmax.second->getCoordinates()[i] + minimumSize;

            systemSize = maxCoordinate - minCoordinate;
            firstCellPosition[i] = minCoordinate;
        }
        cellNumberInDirection[i] = static_cast<std::size_t>(systemSize / minimumSize);
        cellSize[i] = systemSize / cellNumberInDirection[i];

        reserveCellsNumber *= cellSize[i];       
    }
    cells.reserve(reserveCellsNumber);
}

std::vector<AtomPair>& AtomicSystem::getAtomPairs() noexcept { return atomPairs; }

std::vector<Atom>& AtomicSystem::getAtoms() noexcept { return atoms; }
