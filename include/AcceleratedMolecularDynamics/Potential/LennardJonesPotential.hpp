#pragma once
#ifndef TAHD_MORZE_POTENTIAL_H
#define TAHD_MORZE_POTENTIAL_H

#include "Potential/APairPotential.hpp"

namespace md
{
	class LennardJonesPotential : public APairPotential
	{
		double eps;
		double rm;
	public:
		LennardJonesPotential(element first, element second, double eps, double rm, double cutRadius);
		LennardJonesPotential(element el, double eps, double rm, double cutRadius);
		~LennardJonesPotential() override;
		void computeAndSetAccelerations(std::vector<AtomPair>& atomPairs) const override;
	};
}

#endif	//TAHD_MORZE_POTENTIAL_H
