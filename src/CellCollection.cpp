#include "CellCollection.hpp"
#include <algorithm>
#include <exception>

CellCollection::CellCollection(const std::vector<Atom>& atoms, const APotential* potential, 
                               BorderConditions* borderCond)
    : cells{}, borderConditions{ borderCond }
{
    size_t cellsNumber = computeAndSetParameters(atoms, potential);
    createCells(cellsNumber);
    computeAndSetNeighbours();
}

std::array<std::size_t, DIMENSIONAL_NUMBER> CellCollection::getOffsetFactorInDirection() const noexcept
{
    std::array<std::size_t, DIMENSIONAL_NUMBER> offsetFactorInDirection;    
    offsetFactorInDirection[0] = 1;
    for(Vector::projection_index direction = 1; direction < DIMENSIONAL_NUMBER; ++direction)
        offsetFactorInDirection[direction] = offsetFactorInDirection[direction-1] * cellNumberInDirection[direction-1];
    return offsetFactorInDirection;
}

std::array<std::size_t, DIMENSIONAL_NUMBER> CellCollection::getOffsetBySizeInDirection() const noexcept
{
    return getOffsetBySizeInDirection(getOffsetFactorInDirection());
}

std::array<std::size_t, DIMENSIONAL_NUMBER> CellCollection::getOffsetBySizeInDirection(
    const std::array<std::size_t, DIMENSIONAL_NUMBER>& offsetFactorInDirection) const noexcept
{
    std::array<std::size_t, DIMENSIONAL_NUMBER> offsetBySizeInDirection;    
    for(Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
    {
        offsetBySizeInDirection[i] = offsetFactorInDirection[i] * cellNumberInDirection[i];
    }
    return offsetBySizeInDirection;
}

std::size_t CellCollection::computeAndSetParameters(const std::vector<Atom>& atoms, const APotential* potential)
{
    size_t cellsNumber = 1;
    double minimumSize = potential->getCutRadius();
    for(Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
    {
        bool isPeriodic = false;
        if (borderConditions != nullptr)
            isPeriodic = borderConditions->getBorderTypes()[i] == BorderConditions::borderType::periodic;

        double systemSize;
        if (isPeriodic)
        {
            systemSize = borderConditions->getSize()[i];
            firstCellPosition[i] = borderConditions->getZeroPoint()[i];
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
        cellNumberInDirection[i] = static_cast<int64_t>(floor(systemSize / minimumSize));
        cellSize[i] = systemSize / cellNumberInDirection[i];

        cellsNumber *= cellNumberInDirection[i];       
    }
    return cellsNumber;  
}

void CellCollection::createCells(const std::size_t cellsNumber)
{
    cells.reserve(cellsNumber);
    for(std::size_t i = 0; i < cellsNumber; ++i)
        cells.push_back(Cell());
}

void CellCollection::computeAndSetNeighbours()
{
    std::array<std::size_t, DIMENSIONAL_NUMBER> offsetFactorInDirection = getOffsetFactorInDirection();
    std::array<std::size_t, DIMENSIONAL_NUMBER> offsetBySizeInDirection = getOffsetBySizeInDirection(offsetFactorInDirection);
    for (std::size_t p = 0; p < cells.size(); ++p)
    {
        std::vector<std::size_t> neighbourCellsIndexes;
        neighbourCellsIndexes.push_back(p);
        for(Vector::projection_index direction = 0; direction < DIMENSIONAL_NUMBER; ++direction)
        {
            std::size_t initSize = neighbourCellsIndexes.size();
            for (std::size_t k = 0; k < initSize; ++k)
            {
                std::size_t i = neighbourCellsIndexes[k];
                for(int offset = -1; offset <= 1; offset+=2)
                {
                    std::size_t possibleNeighbourIndex = i + offsetFactorInDirection[direction] * offset;

                    if (possibleNeighbourIndex / offsetBySizeInDirection[direction] == 
                                             i / offsetBySizeInDirection[direction])
                    {
                        neighbourCellsIndexes.push_back(possibleNeighbourIndex);
                    }
                    else if (possibleNeighbourIndex < 0)
                    {
                        if (borderConditions != nullptr && 
                            borderConditions->getBorderTypes()[direction] == BorderConditions::borderType::periodic)
                                neighbourCellsIndexes.push_back(possibleNeighbourIndex + offsetBySizeInDirection[direction]);
                    }
                    else
                    {
                        if (borderConditions != nullptr && 
                            borderConditions->getBorderTypes()[direction] == BorderConditions::borderType::periodic)
                                neighbourCellsIndexes.push_back(possibleNeighbourIndex - offset/abs(offset)*offsetBySizeInDirection[direction]);
                    }
                }
            }
        }
        for(auto index: neighbourCellsIndexes)
            cells[p].addNeighborCell(&cells[index]);
    }
}

std::vector<Cell>& CellCollection::getCells() noexcept { return cells; }

const std::vector<Cell>& CellCollection::getCells() const noexcept { return cells; }

Cell& CellCollection::findCellContainingVector(Vector::ConstVectorPass vector)
{
    std::array<std::size_t, DIMENSIONAL_NUMBER> offsetFactorInDirection = getOffsetFactorInDirection();

    Vector pos = vector;
    if (borderConditions != nullptr)
        pos = borderConditions->computePosition(pos);
    
    for(Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
        if (borderConditions == nullptr || 
            borderConditions->getBorderTypes()[i] == BorderConditions::borderType::none)
            pos[i] -= firstCellPosition[i];

    std::size_t cellIndex = 0;
    for(Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
    {
        int64_t cellCoordinate = static_cast<int64_t>(floor(pos[i] / cellSize[i]));

        if (cellCoordinate < 0 || cellCoordinate >= cellNumberInDirection[i])
            throw std::range_error("position outside any Cell");
        
        cellIndex += offsetFactorInDirection[i] * cellCoordinate;
    }
    return cells[cellIndex];
}

Cell& CellCollection::findCellContainingAtom(const Atom& atom)
{
    return findCellContainingVector(atom.getCoordinates());
}
