#include "tests.hpp"
#include "mpi.h"
#include "Parallel/MPI/Processes.hpp"

using namespace md;

namespace testProcessesMPI
{
    void getCount()
    {
        Processes processes;
        int ProcNum;
        MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);

        assert(processes.getCount() == static_cast<unsigned>(ProcNum));
    }

    void getRank()
    {
        Processes processes;
        int ProcRank;
        MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

        assert(processes.getRank() == static_cast<unsigned>(ProcRank));
    }

    void setVelocities()
    {
        Processes processes;
        Vector randomVelocity = randomVector();
        std::vector<Atom> atoms{ Atom{"Cu", {}, randomVelocity} };

        assert(equal(atoms[0].getVelocity(), randomVelocity));
        processes.setVelocities(atoms);
        if (processes.getRank() == 0)
        {
            assert(equal(atoms[0].getVelocity(), randomVelocity));
        }
        if (processes.getRank() != 0)
        {
            assert(!equal(atoms[0].getVelocity(), randomVelocity));
        }

        if (processes.getRank() == 0)
        {
            atoms[0].setVelocity({});
        }
        if (processes.getRank() != 0)
        {
            assert(!equal(atoms[0].getVelocity(), {}));
        }
        processes.setVelocities(atoms);
        assert(equal(atoms[0].getVelocity(), {}));
    }

    void exchangeAccelerations()
    {
        Processes processes;
        std::vector<Atom> atoms;
        Vector acceleration = randomVector();
        std::vector<int> sendCounts;
        for (std::uint8_t i = 0; i < processes.getCount(); ++i)
        {
            sendCounts.push_back(5 * i);
        }
        for (std::size_t i = 0; i < sendCounts.size(); ++i)
        {
            for (int j = 0; j < sendCounts[i]; ++j)
            {
                atoms.emplace_back("Cu", randomPosition());
                if (i == processes.getRank())
                {
                    atoms.back().setAcceleration(acceleration);
                }
            }
        }
        std::vector<Atom*> atomsPointers(atoms.size());
        for (std::size_t i = 0; i < atoms.size(); ++i)
        {
            atomsPointers[i] = &atoms[i];
        }

        std::size_t previousSumm = 0;
        for (std::uint8_t i = 0; i < sendCounts.size(); ++i)
        {
            for (std::uint8_t j = 0; j < sendCounts[i]; ++j)
            {
                if (i == processes.getRank())
                {
                    assert(equal(atoms[previousSumm + j].getAcceleration(), acceleration));
                }
                else 
                {
                    assert(equal(atoms[previousSumm + j].getAcceleration(), {}));
                }
            }
            previousSumm += sendCounts[i];
        }

        processes.exchangeAccelerations(atomsPointers, sendCounts);

        previousSumm = 0;
        for (std::uint8_t i = 0; i < sendCounts.size(); ++i)
        {
            for (std::uint8_t j = 0; j < sendCounts[i]; ++j)
            {
                if (i == processes.getRank())
                {
                    assert(equal(atoms[previousSumm + j].getAcceleration(), acceleration));
                }
                else 
                {
                    assert(!equal(atoms[previousSumm + j].getAcceleration(), acceleration));
                    assert(!equal(atoms[previousSumm + j].getAcceleration(), {}));
                }
            }
            previousSumm += sendCounts[i];
        }
    }
}

void testParallel()
{
    testProcessesMPI::getCount();
    testProcessesMPI::getRank();
    testProcessesMPI::setVelocities();
    testProcessesMPI::exchangeAccelerations();
}
