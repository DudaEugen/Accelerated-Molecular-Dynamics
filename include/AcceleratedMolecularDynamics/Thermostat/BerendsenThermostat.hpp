#pragma once
#ifndef TAHD_BERENDSEN_THERMOSTAT_H
#define TAHD_BERENDSEN_THERMOSTAT_H

#include <functional>
#include "Thermostat/AThermostat.hpp"

namespace md
{
	class BerendsenThermostat: public AThermostat
	{
        double phononsFrequency;
        const std::function<bool(const Atom&)> isAtomFromDissipativeLeyer;

	public:
		BerendsenThermostat(
            double temperature,
            const std::function<bool(const Atom&)>& isAtomFromDissipativeLeyer,
            double phononsFrequency
        ) noexcept;
		~BerendsenThermostat() = default;

		void heatExchange(std::vector<Atom> &atoms) const override;
	};
}

#endif // TAHD_BERENDSEN_THERMOSTAT_H
