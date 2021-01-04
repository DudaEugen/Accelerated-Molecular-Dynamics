#include "ProcessesSet.hpp"
#include <exception>

md::ProcessesSet::ProcessesSet(const unsigned int uniqId, AtomicSystem* atomicSystem, const MPI_Comm mpiComm)  
    : id{ uniqId }, aSystem{ atomicSystem }, commutator{ mpiComm }
{
    int procNumber;
    MPI_Comm_size(commutator, &procNumber);
    processes.reserve(procNumber);
    for(int i = 0; i < procNumber; ++i)
        processes.push_back(Process(i));

    MPI_Comm_rank(commutator, &activeProcessRank);
}

MPI_Comm md::ProcessesSet::getCommutator() const noexcept { return commutator; }

unsigned int md::ProcessesSet::getId() const noexcept { return id; }

void md::ProcessesSet::addAtomicSystem(AtomicSystem& atomicSystem) noexcept
{
    aSystem = &atomicSystem;
}
