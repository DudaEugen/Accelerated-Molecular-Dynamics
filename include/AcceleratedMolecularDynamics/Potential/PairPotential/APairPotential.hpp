#pragma once
#ifndef TAHD_ABSTRACT_PAIR_POTENTIAL_H
#define TAHD_ABSTRACT_PAIR_POTENTIAL_H

#include "Potential/APotential.hpp"

namespace md
{
	class APairPotential: public APotential
	{
	protected:
		double cutRadius;
		std::pair<element, element> elements;

		bool isCorrectElements(const AtomPair& atomPair) const noexcept;
		void computeAndSetAccelerations(NeighboursList& neighboursList) const override;
		// Compute force that acts on the first atom
		virtual Vector computeForce(const AtomPair& pair) const = 0;
	public:
		APairPotential(element first, element second, double cutRadius) noexcept;
		virtual ~APairPotential() = default;
		double getCutRadius() const noexcept override;
	};
}

#endif	//TAHD_ABSTRACT_PAIR_POTENTIAL_H
