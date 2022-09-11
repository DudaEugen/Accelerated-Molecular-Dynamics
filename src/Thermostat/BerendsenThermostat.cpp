#include <cmath>
#include "Thermostat/BerendsenThermostat.hpp"

md::BerendsenThermostat::BerendsenThermostat(
	double temperature,
	const std::function<bool(const Atom&)>& isAtomFromDissipativeLeyer,
	double debyeTemperature
) noexcept
	: AThermostat{ temperature },
	isAtomFromDissipativeLeyer{ isAtomFromDissipativeLeyer },
	debyeTemperature{ debyeTemperature }
{
}

void md::BerendsenThermostat::heatExchange(std::vector<Atom> &atoms) const
{
	double summaryKineticEnergy = 0;
	double noFrozenAtomsCount = 0;
	std::vector<Atom*> dissipativeLeyers;
	for (auto& atom: atoms)
	{
		if (!atom.isFrozen())
		{
			summaryKineticEnergy += atom.mass * atom.getVelocity().sumSquares() / 2;
			noFrozenAtomsCount += 1;
			if (isAtomFromDissipativeLeyer(atom))
			{
				dissipativeLeyers.push_back(&atom);
			}
		}
	}
	double currentTemperature = 2 / kDimensionalNumber * summaryKineticEnergy / (noFrozenAtomsCount * kBoltzmann);
	double factor = - 0.75 * debyeTemperature * kBoltzmann * 2 * M_PI / kPlank * (1 - temperature / currentTemperature);

	for (auto* atom: dissipativeLeyers)
	{
		atom->addAcceleration(factor * atom->mass * atom->getVelocity());
	}
}
