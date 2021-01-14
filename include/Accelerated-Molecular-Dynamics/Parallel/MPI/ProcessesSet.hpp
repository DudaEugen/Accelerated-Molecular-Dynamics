#pragma once
#ifndef TAHD_PROCESSES_SET_H
#define TAHD_PROCESSES_SET_H

#include <cstddef>
#include <cstdlib>
#include "mpi.h"
#include "Process.hpp"
#include "System/AtomicSystem.hpp"

namespace md
{
    /*ProcessesSet is set of processes that working on one system. 
    One program can start several such processes at once, 
    working with different atomic systems or the same systems with different initial conditions. 
    Each set of processes has its own MPI commutator. These commutators must not overlap
    ProcessesSet is responsible for the interaction of processes within the same commutator.*/
    class ProcessesSet 
    {
        std::vector<Process> processes;
        AtomicSystem* aSystem;
        MPI_Comm commutator;
        int activeProcessRank;  //control is transferred to this process after data exchange between processes
        unsigned int id; 
    public:
        ProcessesSet(const unsigned int uniqId = 0, AtomicSystem* atomicSystem = nullptr, 
                    const MPI_Comm mpiComm = MPI_COMM_WORLD);
        MPI_Comm getCommutator() const noexcept;
        unsigned int getId() const noexcept;
        void addAtomicSystem(AtomicSystem& atomicSystem) noexcept;
    };

    // create N ProcessesSets and return active for this process ProcessesSet
    // to i-th ProcessesSet corresponding atomicSystems[i]
    template<std::size_t N>
    ProcessesSet createProcessesSets(MPI_Comm initialComm = MPI_COMM_WORLD, AtomicSystem* atomicSystem = nullptr)
    {
        MPI_Comm newComm;
        int ProcRank, ProcNum;
        MPI_Comm_size(initialComm, &ProcNum);
        MPI_Comm_rank(initialComm, &ProcRank);
        int setId = ProcRank % N;
        
        if (ProcNum >= N)
            MPI_Comm_split(initialComm, setId, 0, &newComm);
        else
            throw std::invalid_argument("varible 'number' great that Number of processes in commutator");
        
        return ProcessesSet(setId, atomicSystem, newComm);
    }
}

#endif  //TAHD_PROCESSES_SET_H
