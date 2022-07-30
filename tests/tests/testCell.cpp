#include "tests.hpp"
#include "System/CellCollection.hpp"
#include "BoundaryConditions/DimensionsCondition/IDimensionsCondition.hpp"
#include "BoundaryConditions/DimensionsCondition/PeriodicDimension.hpp"
#include "BoundaryConditions/BoundaryConditions.hpp"

using namespace md;

namespace testCellClass
{
    void constructor()
    {
        Cell cell;
        assert(cell.getAtoms().size() == 0);
    }

    void methods()
    {
        Cell cell;
        std::size_t count = std::rand() % 100;
        Atom atom{"Al", randomPosition()};
        for (std::size_t i = 0; i < count; ++i)
        {
            cell.addAtom(atom);
        }
        assert(cell.getAtoms().size() == count);
        cell.clear();
        assert(cell.getAtoms().size() == 0);
    }
}

void testCell()
{
    testCellClass::constructor();
    testCellClass::methods();
}
