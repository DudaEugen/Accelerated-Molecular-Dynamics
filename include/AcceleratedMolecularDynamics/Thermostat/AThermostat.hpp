#pragma once
#ifndef TAHD_ABSTRACT_THERMOSTAT_H
#define TAHD_ABSTRACT_THERMOSTAT_H

#include <vector>
#include "Atoms/Atom.hpp"

namespace md
{
	class AThermostat
	{
	protected:
		double temperature;

	public:
		AThermostat(double temperature) noexcept;
		virtual ~AThermostat() = 0;
		double getTemperature() const noexcept;
		void setTemperature(double newTemperature) noexcept;
		virtual void heatExchange(std::vector<Atom> &atoms) const = 0;
	};
}

#endif // TAHD_ABSTRACT_THERMOSTAT_H
