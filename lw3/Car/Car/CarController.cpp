#include "CarController.h"
#include <sstream>

CarController::CarController(std::istream& input, std::ostream& output)
	: m_input(input)
	, m_output(output)
	, m_actionMap({
			{ "Info", [this](std::istream& input) { Info(input);}},
			{ "EngineOn", [this](std::istream& input) { EngineOn(input); } },
			{ "EngineOff", [this](std::istream& input) { EngineOff(input); } },
			{ "SetGear", [this](std::istream& input) { SetGear(input); } },
			{ "SetSpeed", [this](std::istream& input) { SetSpeed(input); } }
		})
{
}

void CarController::HandleUserInput(const std::string& line)
{
	std::istringstream str(line);
	std::string command;

	str >> command;
	auto it = m_actionMap.find(command);
	if (it == m_actionMap.end())
	{
		throw std::runtime_error("Unknown command\n");
	}
	it->second(str);
}

void CarController::Info(std::istream& input) const
{
	m_output << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << "\n"
		<< "Direction: " << PrintDirection(m_car.GetDirection()) << "\n"
		<< "Speed: " << m_car.GetSpeed() << "\n"
		<< "Gear: " << static_cast<int>(m_car.GetGear()) << "\n";
}

void CarController::EngineOn(std::istream& input)
{
	m_car.TurnOnEngine();
}

void CarController::EngineOff(std::istream& input)
{
	m_car.TurnOffEngine();
}

void CarController::SetGear(std::istream& input)
{
	std::string gearStr;
	input >> gearStr;

	try
	{
		int gear = stoi(gearStr);
		m_car.SetGear(gear);
	}
	catch (const std::exception& e)
	{
		m_output << e.what();
	}
}

void CarController::SetSpeed(std::istream& input)
{
	std::string speedStr;
	input >> speedStr;

	try
	{
		int speed = stoi(speedStr);
		m_car.SetSpeed(speed);
	}
	catch (const std::exception& e)
	{
		m_output << e.what();
	}
}

std::string CarController::PrintDirection(const Direction& direction) const
{

	switch (direction)
	{
	case Direction::Backward:
		return "backward";
	case Direction::StandingStill:
		return "standing still";
	case Direction::Forward:
		return "forward";
	default:
		return "Unknow direction";
	}
}
