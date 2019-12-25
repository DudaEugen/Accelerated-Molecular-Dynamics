#pragma once
#ifndef TAHD_ABSTRACT_THERMOSTAT_H
#define TAHD_ABSTRACT_THERMOSTAT_H

#include <vector>
#include "../AtomGroup.h"

class AThermostat
{
protected:
	double T0;							//Temperature of thermostat
	double T;							//Temperature of System
	AtomGroup atomsDissipativeLeyers;	//if Thermostat using dissipative leyers
	std::vector<Atom>& atomsSystem;		//pointer to all moving atoms of System
public:
	virtual ~AThermostat() = 0;
	void setTemperature(const double temperature);
	/*For using instead of AtomGroup property in children classes if necessary*/
	virtual void setAtomList(std::vector<Atom>& atoms);
	double computeTemperature();
	virtual void heatExchange() = 0;
};

#endif	//TAHD_ABSTRACT_THERMOSTAT_H