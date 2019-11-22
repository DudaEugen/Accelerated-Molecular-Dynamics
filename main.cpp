#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <ctime>
#include <stdlib.h>
#include "mpi.h"

using namespace std;

int main(int argc, char* argv[])
{
	int ProcRank, ProcNum;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	
	MPI_Finalize();

	return 0;
}
