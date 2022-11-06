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

        std::vector<double> convertVectorsToValues(const std::vector<Vector> vectors) const;
        std::vector<Vector> convertValuesToVectors(const std::vector<double> vectors) const;

    public:
        Processes();
        ~Processes() = default;

        unsigned getCount() const noexcept;
        unsigned getRank() const noexcept;

        void broadcast(std::vector<double>& data, unsigned root = 0) const;
        void broadcast(std::vector<Vector>& data, unsigned root = 0) const;
        void gatherToAll(std::vector<double>& data, const std::vector<int>& sendCounts) const;
        void gatherToAll(std::vector<Vector>& data, const std::vector<int>& sendCounts) const;

        void setVelocities(std::vector<Atom>& atoms, unsigned root = 0) const;
        void exchangeAccelerations(std::vector<Atom*>& atoms, const std::vector<int>& sendCounts) const;
    };
}

#endif // TAHD_ATOM_GROUP_H
