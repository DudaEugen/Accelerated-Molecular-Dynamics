#pragma once
#ifndef TAHD_ABSTRACT_THERMOSTAT_H
#define TAHD_ABSTRACT_THERMOSTAT_H

#include <vector>
#include "PartOfSystem/AtomGroup.hpp"

namespace md
{
	class AThermostat
	{
	protected:
		double T0;							//Temperature of thermostat
		double T;							//Temperature of System
		std::vector<Atom>& atomsOfSystem;   //pointer to all moving atoms of System
	public:
		AtomGroup dissipativeLeyers;
		AThermostat(std::vector<Atom>& atoms, double temperature) noexcept;
		virtual ~AThermostat() = 0;
		void setTemperature(const double temperature) noexcept;
		double computeTemperature();		//units of velocity is Angstrom/ps
		virtual void heatExchange() = 0;
	};
}

#endif	//TAHD_ABSTRACT_THERMOSTAT_H
