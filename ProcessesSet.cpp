#include "ProcessesSet.h"

ProcessesSet::ProcessesSet(AtomicSystem& atomicSystem, MPI_Comm mpiComm)  
    : aSystem{ &atomicSystem }, commutator{ mpiComm }
{
    int procNumber;
    MPI_Comm_size(commutator, &procNumber);
    processes.reserve(procNumber);
    for(int i = 0; i < procNumber; ++i)
        processes.push_back(Process(i, aSystem->getAtoms().size()));

    MPI_Comm_rank(commutator, &activeProcessRank);
}
