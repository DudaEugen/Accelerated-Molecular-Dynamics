#include "AThermostat.h"

AThermostat::~AThermostat() {
}

void AThermostat::setTemperature(const double temperature)
{
	this->T0 = temperature;
}

double AThermostat::computeTemperature()
{
	T = 0;
	size_t atomNumber = atomsSystem.size();
	for (size_t i = 0; i < atomNumber; ++i)
	{
		T += atomsSystem[i].mass * atomsSystem[i].getVelocity().sumSquares();
	}
	T *= 10000 / (K_BOLTZMANN * DIMENSIONAL_NUMBER * atomNumber);	//units of velocity is Angstrom/ps^2
	return T;
}
