#include "Thermostat/BerendsenThermostat.hpp"

md::BerendsenThermostat::BerendsenThermostat(
	double temperature,
	const std::function<bool(const Atom&)>& isAtomFromDissipativeLeyer,
	double phononsFrequency
) noexcept
	: AThermostat{ temperature },
	isAtomFromDissipativeLeyer{ isAtomFromDissipativeLeyer },
	phononsFrequency{ phononsFrequency }
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
	double factor = - 0.75 * phononsFrequency * kBoltzmann / kPlank * (1 - temperature / currentTemperature);

	for (auto* atom: dissipativeLeyers)
	{
		atom->addAcceleration(factor * atom->getVelocity());	// TODO: check units
	}
}
