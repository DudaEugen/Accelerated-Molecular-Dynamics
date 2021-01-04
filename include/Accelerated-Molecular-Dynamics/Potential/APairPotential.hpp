#pragma once
#ifndef TAHD_ABSTRACT_PAIR_POTENTIAL_H
#define TAHD_ABSTRACT_PAIR_POTENTIAL_H

#include "Potential/APotential.hpp"

namespace md
{
	class APairPotential: public APotential
	{
	protected:
		std::vector<std::size_t> indexes;		// contain indexes of pairTypes for corresponding atomPairs
		std::vector<std::pair<element, element>> pairTypes;
		std::vector<double> rc;

		bool addPairType(const element first, const element second);
	public:
		APairPotential(std::vector<AtomPair>* atomPairs, const std::size_t maxAtomPairTypes = 0);
		virtual ~APairPotential() = default;
		void refreshAtomPairs();
		double getCutRadius() const noexcept override;
	};
}

#endif	//TAHD_ABSTRACT_PAIR_POTENTIAL_H
