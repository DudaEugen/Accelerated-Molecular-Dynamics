#include "AThermostat.h"

AThermostat::~AThermostat() {
}

void AThermostat::setTemperature(const double temperature)
{
	this->T0 = temperature;
}

void AThermostat::setAtomList(std::vector<Atom>& atoms)
{
	size_t size = atoms.size();
	atomsDissipativeLeyers.clearList();
	for (size_t i = 0; i < size; ++i)
	{
		atomsDissipativeLeyers.addAtom(&atoms[i]);
	}
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
