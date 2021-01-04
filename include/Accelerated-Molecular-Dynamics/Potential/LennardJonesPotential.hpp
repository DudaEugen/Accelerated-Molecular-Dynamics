#pragma once
#ifndef TAHD_MORZE_POTENTIAL_H
#define TAHD_MORZE_POTENTIAL_H

#include "Potential/APairPotential.hpp"

namespace md
{
	class LennardJonesPotential : public APairPotential
	{
		std::vector<double> eps;
		std::vector<double> rm;
	public:
		LennardJonesPotential(std::vector<AtomPair>* atomPairs, const std::size_t maxAtomPairTypes);
		~LennardJonesPotential() override;
		void addPairType(element first, element second, 
						 double bondEnergy, double bondRadius, double cutRadius);
		// bondEnergy(eV), bondRadius(A), cutradius(A)

		void computeAndSetAccelerations() override;
	};
}

#endif	//TAHD_MORZE_POTENTIAL_H
