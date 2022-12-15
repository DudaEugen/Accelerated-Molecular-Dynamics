#pragma once
#ifndef TAHD_ABSTRACT_PAIR_POTENTIAL_H
#define TAHD_ABSTRACT_PAIR_POTENTIAL_H

#include "Potential/APotential.hpp"
#include "Potential/Function.hpp"

namespace md
{
	class APairPotential: public APotential
	{
		IBaseFunction* function;
		double cutRadius;
		std::pair<element, element> elements;
	protected:
		bool isCorrectElements(const AtomPair& atomPair) const noexcept;
		double energy(double distance) const;
		double derivative(double distance) const;
	public:
		APairPotential(element first, element second, IBaseFunction* function, double cutRadius) noexcept;
		virtual ~APairPotential();
		void addAccelerations(NeighboursList& neighboursList) const override;
		double getCutRadius() const noexcept override;
	};
}

#endif	//TAHD_ABSTRACT_PAIR_POTENTIAL_H
