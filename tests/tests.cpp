#include <iostream>
#include "mpi.h"
#include "tests.hpp"

int main(int argc, char* argv[])
{
	int ProcRank, ProcNum;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	
	testParallel();
	for (int i = 0; i < ProcNum; ++i)
	{
		MPI_Barrier(MPI_COMM_WORLD);
		if (i == ProcRank)
		{
			testVector();
			testElement();
			testMoveAlgorithm();
			testAtom();
			testSubstance();
			testBoundaryConditions();
			testMatrix();
			testAtomPair();
			testCell();
			testZip();
			testDerivative();

			std::cout << "tests completed\n";
		}
	}

	MPI_Finalize();

	return 0;
}
