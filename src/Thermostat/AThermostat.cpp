#include "Thermostat/AThermostat.hpp"

md::AThermostat::AThermostat(double temperature) noexcept
	: temperature{ temperature }
{
}

md::AThermostat::~AThermostat() = default;

double md::AThermostat::getTemperature() const noexcept
{
	return temperature;
}

void md::AThermostat::setTemperature(double newTemperature) noexcept
{ 
	temperature = newTemperature;
}
