#include "Thermostat/AThermostat.hpp"

md::AThermostat::AThermostat(std::vector<Atom>& atoms, double temperature) noexcept
	: T0{ temperature }, T{ temperature }, atomsOfSystem{ atoms }
{
}

void md::AThermostat::setTemperature(const double temperature) noexcept { T0 = temperature; }

double md::AThermostat::computeTemperature()
{
	T = 0;
	for (auto& atom: atomsOfSystem)
	{
		T += atom.mass * atom.getVelocity().sumSquares();
	}
	T *= 10000 / (kBoltzmann * kDimensionalNumber * atomsOfSystem.size());	//units of velocity is Angstrom/ps
	return T;
}
