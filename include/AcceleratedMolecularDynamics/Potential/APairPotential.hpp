#pragma once
#ifndef TAHD_ABSTRACT_PAIR_POTENTIAL_H
#define TAHD_ABSTRACT_PAIR_POTENTIAL_H

#include "Potential/IPotential.hpp"
#include "Atoms/AtomPair.hpp"

namespace md
{
	class APairPotential: public IPotential
	{
	protected:
		double cutRadius;
		std::pair<element, element> elements;

		bool isCorrectElements(const AtomPair& atomPair) const noexcept;
	public:
		APairPotential(element first, element second, double cutRadius) noexcept;
		virtual ~APairPotential() = default;
		double getCutRadius() const noexcept override;
	};
}

#endif	//TAHD_ABSTRACT_PAIR_POTENTIAL_H
