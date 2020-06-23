#pragma once
#ifndef TAHD_MORZE_POTENTIAL_H
#define TAHD_MORZE_POTENTIAL_H

#include "IPotential.h"

class MorsePotential : public IPotential
{
	double De;
	double re;
	double a;
	double rc;
public:
	MorsePotential(double dissociationEnergy, double equilibriumBondDistance, double a, double cutRadius);	// dissociationEnergy(eV), equilibriumBondDistance(A), a(A^-1), cutradius(A)
	~MorsePotential() override;
	virtual void computeAndSetAccelerations(const std::vector<AtomPair>& pairs) override;
	virtual double getCutRadius() const override;
};

#endif	//TAHD_MORZE_POTENTIAL_H
