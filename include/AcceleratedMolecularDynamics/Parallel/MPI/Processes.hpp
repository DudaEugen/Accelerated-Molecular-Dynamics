#pragma once
#ifndef TAHD_PROCESSES_H
#define TAHD_PROCESSES_H

#include <vector>
#include "Atoms/Atom.hpp"

namespace md
{
    class Processes
    {
    private:
        const int count;
        const int rank;

        static int defineCount();
        static int defineRank();

        void broadcast(std::vector<double>& data) const;
        void gatherToAll(std::vector<double>& data, const std::vector<int>& sendCounts) const;

    public:
        Processes();
        ~Processes() = default;

        unsigned getCount() const noexcept;
        unsigned getRank() const noexcept;

        void exchangeValues(std::vector<double>& values, const std::vector<int>& sendCounts) const;

        void setVelocities(std::vector<Atom>& atoms) const;
        void exchangeAccelerations(std::vector<Atom*>& atoms, const std::vector<int>& sendCounts) const;
    };
}

#endif // TAHD_ATOM_GROUP_H
