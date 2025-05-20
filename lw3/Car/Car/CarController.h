#pragma once

#include <iostream>
#include <map>
#include <functional>
#include <string>
#include "Car.h"

class CarController
{
public:
	CarController(std::istream& input, std::ostream& output);
	void HandleUserInput(const std::string& line);

private:
	std::istream& m_input;
	std::ostream& m_output;

	Car m_car;

	using Handler = std::function<void(std::istream&)>;
	using ActionMap = std::map<std::string, Handler>;
	const ActionMap m_actionMap;

	void Info(std::istream& input) const;
	void EngineOn(std::istream& input);
	void EngineOff(std::istream& input);
	void SetGear(std::istream& input);
	void SetSpeed(std::istream& input);

	std::string PrintDirection(const Direction& direction) const;
};