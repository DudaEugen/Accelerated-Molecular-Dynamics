#pragma once
#ifndef TAHD_ABSTRACT_POTENTIAL_H
#define TAHD_ABSTRACT_POTENTIAL_H

#include <vector>
#include "NeighboursList/NeighboursList.hpp"

namespace md
{
	class APotential
	{
		void discardAccelerations(std::vector<Atom>& atoms) const;
	protected:
		virtual void computeAndSetAccelerations(NeighboursList& neighboursList) const = 0;
	public:
		virtual ~APotential() = 0;
		void computeAndSetAccelerations(NeighboursList& neighboursList, std::vector<Atom>& atoms) const;
		virtual double getCutRadius() const noexcept = 0;
	};
}

#endif	//TAHD_ABSTRACT_POTENTIAL_H
