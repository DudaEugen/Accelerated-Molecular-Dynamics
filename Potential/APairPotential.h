#pragma once
#ifndef TAHD_ABSTRACT_PAIR_POTENTIAL_H
#define TAHD_ABSTRACT_PAIR_POTENTIAL_H

#include "IPotential.h"

class APairPotential: public IPotential
{
protected:
	std::vector<std::size_t> indexes;			// contain indexes of pairTypes for corresponding atomPairs
	std::vector<std::pair<element, element>> pairTypes;
	std::vector<double> rc;
	std::vector<AtomPair>* atomPairs;

	bool addPairType(const element first, const element second);
public:
	APairPotential(const std::size_t maxAtomPairTypes);
	virtual ~APairPotential() = default;
	void setAtomPairs(std::vector<AtomPair>& pairs);
	double getCutRadius() const override;
};

#endif	//TAHD_ABSTRACT_PAIR_POTENTIAL_H
