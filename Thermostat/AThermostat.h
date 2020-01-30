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
public:
	AtomGroup dissipativeLeyers;
	virtual ~AThermostat() = 0;
	void setTemperature(const double temperature);
	double computeTemperature();
	virtual void heatExchange() = 0;
};

#endif	//TAHD_ABSTRACT_THERMOSTAT_H