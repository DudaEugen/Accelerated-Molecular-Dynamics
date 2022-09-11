#pragma once
#ifndef TAHD_ATOMIC_SYSTEM_H
#define TAHD_ATOMIC_SYSTEM_H

#include <vector>
#include "Potential/IPotential.hpp"
#include "Thermostat/AThermostat.hpp"
#include "NeighboursList/NeighboursList.hpp"

namespace md
{
	class AtomicSystem
	{
		std::vector<Atom> atoms;
		std::vector<IPotential*> potentials;
		NeighboursList neighboursList;
		AThermostat* thermostat;

	public:
		AtomicSystem(
			const std::vector<Atom>& allAtoms,
			IPotential* atomicPotential,
			AThermostat* thermostat
		);
		AtomicSystem(
			const std::vector<Atom>& allAtoms,
			std::vector<IPotential*> potentials,
			AThermostat* thermostat
		);
		~AtomicSystem();

		void run(double time, double timeStep);
		void setRandomVelocities();
	};
}

#endif	//TAHD_ATOMIC_SYSTEM_H
