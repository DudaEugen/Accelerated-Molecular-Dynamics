#pragma once
#ifndef TAHD_MORZE_POTENTIAL_H
#define TAHD_MORZE_POTENTIAL_H

#include "APairPotential.h"

class MorsePotential : public APairPotential
{
	std::vector<double> De;
	std::vector<double> re;
	std::vector<double> a;
public:
	MorsePotential(AtomicSystem* s, const std::size_t maxAtomPairTypes);
	~MorsePotential() override;
	void addPairType(element first, element second, double dissociationEnergy, double equilibriumBondDistance, double a, double cutRadius);	
	// dissociationEnergy(eV), equilibriumBondDistance(A), a(A^-1), cutradius(A)

	void computeAndSetAccelerations() override;
};

#endif	//TAHD_MORZE_POTENTIAL_H
