#pragma once
#ifndef TAHD_ABSTRACT_THERMOSTAT_H
#define TAHD_ABSTRACT_THERMOSTAT_H

#include <vector>
#include "Part of System/AtomGroup.hpp"

namespace md
{
	class AThermostat
	{
	protected:
		double T0;							//Temperature of thermostat
		double T;							//Temperature of System
		std::vector<Atom>& atomsSystem;		//pointer to all moving atoms of System
	public:
		AtomGroup dissipativeLeyers;
		virtual ~AThermostat() = 0;
		void setTemperature(const double temperature) noexcept;
		double computeTemperature();		//units of velocity is Angstrom/ps
		virtual void heatExchange() = 0;
	};
}

#endif	//TAHD_ABSTRACT_THERMOSTAT_H
