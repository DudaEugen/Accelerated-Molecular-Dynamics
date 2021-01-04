#include "Thermostat/AThermostat.hpp"

void md::AThermostat::setTemperature(const double temperature) noexcept { T0 = temperature; }

double md::AThermostat::computeTemperature()
{
	T = 0;
	size_t atomNumber = atomsSystem.size();
	for (size_t i = 0; i < atomNumber; ++i)
	{
		T += atomsSystem[i].mass * atomsSystem[i].getVelocity().sumSquares();
	}
	T *= 10000 / (K_BOLTZMANN * DIMENSIONAL_NUMBER * atomNumber);	//units of velocity is Angstrom/ps
	return T;
}
