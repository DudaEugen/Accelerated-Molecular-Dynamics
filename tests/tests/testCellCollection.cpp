#include "../tests.hpp"
#include "System/CellCollection.hpp"
#include "../Potential/MockPotential.hpp"

using namespace md;

void testCellCollectionDimensionalNumber3()
{
    if constexpr (DIMENSIONAL_NUMBER == 3)
	{
		std::array<BorderConditions::borderType, DIMENSIONAL_NUMBER> bTypes = {
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
			BorderConditions::borderType::periodic,
		};
		BorderConditions bCond(Vector{8, 10, 47}, bTypes);
		APotential* potential = new MockPotential(4);
		std::vector<Atom> atoms = { Atom{"Cu", Vector{}}, Atom{"Cu", Vector{13, 12.1, 12}}};
		CellCollection cc{ atoms, potential, &bCond };
		assert(cc.getCells().size() == 44);

		CellCollection cellCollection{ atoms, potential};
		assert(cellCollection.getCells().size() >= 27);
		int* neighbourCellNumber = new int[30]();	// neighbourCellNumber[i] is number of cell that have i neighbours
		for(auto& cell: cellCollection.getCells())
			++neighbourCellNumber[cell.getNeighborCells().size()];
		for(int i = 0; i < 30; ++i)
		{
			if (i == 8)
				assert(neighbourCellNumber[i] == 8);
			else if ( i==12 || i==18 || i == 27)
				assert(neighbourCellNumber[i] > 0);
			else
				assert(neighbourCellNumber[i] == 0);	
		}
		delete[] neighbourCellNumber;
		int i = 0;
		try
		{
			cellCollection.findCellContainingVector(Vector{1000, -1000, 0});
		}
		catch(const std::range_error& e)
		{
			i = 1;
		}
		assert(i == 1);	
	}
}

void testCellCollectionNeighborsCells()
{
    std::array<BorderConditions::borderType, DIMENSIONAL_NUMBER> bordersType;
	for (Vector::projection_index i = 0; i < DIMENSIONAL_NUMBER; ++i)
		bordersType[i] = BorderConditions::borderType::periodic;
	Vector vect = randomVector<20, 50>();
	BorderConditions bConditions(vect, bordersType);
	APotential* pot = new MockPotential(6);
	std::vector<Atom> twoAtoms = { Atom{"Cu", Vector{}}, Atom{"Cu", vect}};

	CellCollection cColl{ twoAtoms, pot, &bConditions };
	for(auto& cell: cColl.getCells())
	{
		assert(cell.getNeighborCells().size() == static_cast<std::size_t>(round(pow(3, DIMENSIONAL_NUMBER))));
		bool isFindSelf = false;
		for(auto c: cell.getNeighborCells())
			if (c == &cell)
			{
				isFindSelf = true;
				break;
			}
		assert(isFindSelf);
	}
	Vector v = randomVector();
	assert(&cColl.findCellContainingVector(v) == &cColl.findCellContainingAtom(Atom{"Cu", v}));

	CellCollection cellColl{ twoAtoms, pot};
	for(auto& cell: cellColl.getCells())
	{
		bool isFindSelf = false;
		for(auto c: cell.getNeighborCells())
			if (c == &cell)
			{
				isFindSelf = true;
				break;
			}
		assert(isFindSelf);
	}
}

void testCellCollection()
{
	testCellCollectionNeighborsCells();

    if constexpr (DIMENSIONAL_NUMBER == 3)
    {
        testCellCollectionDimensionalNumber3();
    }
}
