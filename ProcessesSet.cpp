#include "ProcessesSet.h"
#include <exception>

ProcessesSet::ProcessesSet(const unsigned int uniqId, AtomicSystem* atomicSystem, const MPI_Comm mpiComm)  
    : id{ uniqId }, aSystem{ atomicSystem }, commutator{ mpiComm }
{
    int procNumber;
    MPI_Comm_size(commutator, &procNumber);
    processes.reserve(procNumber);
    for(int i = 0; i < procNumber; ++i)
        processes.push_back(Process(i));

    MPI_Comm_rank(commutator, &activeProcessRank);
}

MPI_Comm ProcessesSet::getCommutator() const noexcept { return commutator; }

unsigned int ProcessesSet::getId() const noexcept { return id; }

void ProcessesSet::addAtomicSystem(AtomicSystem& atomicSystem) noexcept
{
    aSystem = &atomicSystem;
}
