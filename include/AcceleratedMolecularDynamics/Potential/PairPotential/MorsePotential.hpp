#pragma once
#ifndef TAHD_MORZE_POTENTIAL_H
#define TAHD_MORZE_POTENTIAL_H

#include "Potential/PairPotential/APairPotential.hpp"

namespace md
{
	class MorsePotential : public APairPotential
	{
		double De;
		double re;
		double a;
	protected:
		double energy(double distance) const override;
		double derivative(double distance) const override;
	public:
		MorsePotential(element el, double De, double re, double a, double cutRadius);
		MorsePotential(element first, element second, double De, double re, double a, double cutRadius);
		~MorsePotential() override;
	};
}

#endif	//TAHD_MORZE_POTENTIAL_H
