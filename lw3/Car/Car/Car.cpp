#include "Car.h"
#include <iostream>
#include <map>

using SpeedLimit = std::pair<int, int>;

const std::map<int, SpeedLimit> GEAR_SPEAD_LIMITS =
{
	{ -1, { 0, 20 } },
	{ 0, { 0, INT_MAX } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } },
};

bool Car::IsTurnedOn() const
{
	return m_engineIsOn;
}

Direction Car::GetDirection() const
{
	if (m_speed > 0)
	{
		return Direction::Forward;
	}
	else if (m_speed == 0)
	{
		return Direction::StandingStill;
	}
	else
	{
		return Direction::Backward;
	}
}

int Car::GetSpeed() const
{
	return std::abs(m_speed);
}

Gear Car::GetGear() const
{
	return m_gear;
}

void Car::TurnOnEngine()
{
	if (!m_engineIsOn)
	{
		m_engineIsOn = true;
		m_gear = Gear::NeutralGear;
		m_speed = 0;
	}
}

void Car::TurnOffEngine()
{
	if (m_gear == Gear::NeutralGear && m_speed == 0)
	{
		m_engineIsOn = false;
		return;
	}
	throw std::runtime_error("Car must be stopped and in neutral gear\n");
}

bool IsSpeedInLimit(int speed, int minSpeed, int maxSpeed)
{
	return speed >= minSpeed && speed <= maxSpeed;
}

void Car::SetGear(int gear)
{
	if (gear > 5 || gear < -1)
	{
		throw std::invalid_argument("Invalid gear\n");
	}
	if (gear == 0)
	{
		m_gear = Gear::NeutralGear;
	}
	else
	{
		if (!m_engineIsOn)
		{
			throw std::runtime_error("Ñannot set gear while engine is off\n");
		}
	}
	if (gear == -1 && m_gear != Gear::ReverseGear)
	{
		if (m_speed == 0) 
		{
			m_gear = Gear::ReverseGear; 
			return;
		}
		throw std::runtime_error("Cannot reverse while moving\n");
	}
	if (m_gear == Gear::ReverseGear && gear > 0 && m_speed != 0 || m_gear == Gear::NeutralGear && gear > 0 && m_speed < 0) 
	{
		throw std::runtime_error("Cannot reverse while moving\n");
	}
	const auto [minSpeed, maxSpeed] = GEAR_SPEAD_LIMITS.at(gear);
	if (IsSpeedInLimit(std::abs(m_speed), minSpeed, maxSpeed))
	{
		m_gear = static_cast<Gear>(gear);
		return;
	}
	throw std::runtime_error("Unsuitable current speed\n");
}

void Car::SetSpeed(int speed)
{
	if (speed < 0)
	{
		throw std::invalid_argument("Speed cannot be negative\n");
	}
	if (!m_engineIsOn) 
	{
		throw std::runtime_error("Cannot set speed while engine is off\n");
	}

	const auto [minSpeed, maxSpeed] = GEAR_SPEAD_LIMITS.at(static_cast<int>(m_gear));

	if (m_gear == Gear::NeutralGear)
	{
		if (speed <= std::abs(m_speed))
		{
			m_speed = (m_speed < 0) ? -speed : speed;
			return;
		}
		throw std::runtime_error("Cannot accelerate on neutral\n");
	}
	else
	{
		if (IsSpeedInLimit(speed, minSpeed, maxSpeed))
		{
			m_speed = (m_gear == Gear::ReverseGear) ? -speed : speed;
			return;
		}
		throw std::runtime_error("Speed is out of gear range\n");
	}

}

