#pragma once
#ifndef TAHD_ABSTRACT_PAIR_POTENTIAL_H
#define TAHD_ABSTRACT_PAIR_POTENTIAL_H

#include "Potential/APotential.hpp"

namespace md
{
	class APairPotential: public APotential
	{
		double cutRadius;
		std::pair<element, element> elements;
	protected:
		bool isCorrectElements(const AtomPair& atomPair) const noexcept;
		virtual double derivative(const AtomPair& pair) const = 0;
	public:
		APairPotential(element first, element second, double cutRadius) noexcept;
		virtual ~APairPotential() = default;
		void addAccelerations(NeighboursList& neighboursList) const override;
		double getCutRadius() const noexcept override;
	};
}

#endif	//TAHD_ABSTRACT_PAIR_POTENTIAL_H
