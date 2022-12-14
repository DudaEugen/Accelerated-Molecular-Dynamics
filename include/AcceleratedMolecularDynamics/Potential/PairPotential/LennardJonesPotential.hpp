#pragma once
#ifndef TAHD_MORZE_POTENTIAL_H
#define TAHD_MORZE_POTENTIAL_H

#include "Potential/PairPotential/APairPotential.hpp"

namespace md
{
	class LennardJonesPotential : public APairPotential
	{
	public:
		LennardJonesPotential(element first, element second, double eps, double rm, double cutRadius);
		LennardJonesPotential(element el, double eps, double rm, double cutRadius);
		~LennardJonesPotential() override;
	};
}

#endif	//TAHD_MORZE_POTENTIAL_H
