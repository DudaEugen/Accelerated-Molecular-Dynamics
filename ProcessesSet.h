#pragma once
#ifndef TAHD_PROCESSES_SET_H
#define TAHD_PROCESSES_SET_H

#include "mpi.h"
#include "Process.h"
#include "AtomicSystem.h"

/*ProcessesSet is set of processes that working on one system. One program can start several such processes at once, 
working with different atomic systems or the same systems with different initial conditions. 
Each set of processes has its own MPI commutator. These commutators must not overlap
ProcessesSet is responsible for the interaction of processes within the same commutator.*/
class ProcessesSet 
{
    std::vector<Process> processes;
    AtomicSystem* aSystem;
    MPI_Comm commutator;
    int activeProcessRank;  //control is transferred to this process after data exchange between processes 
public:
    ProcessesSet(AtomicSystem& atomicSystem, MPI_Comm mpiComm = MPI_COMM_WORLD);
};

#endif  //TAHD_PROCESSES_SET_H
