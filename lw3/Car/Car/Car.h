#pragma once

enum class Gear
{
	ReverseGear = -1,
	NeutralGear,
	FirstGear,
	SecondGear,
	ThirdGear,
	ForthGear,
	FifthGear
};

enum class Direction
{
	Backward = -1,
	StandingStill,
	Forward
};

class Car
{
public:
	Car() = default;

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;

	void TurnOnEngine();
	void TurnOffEngine();
	void SetGear(int gear);
	void SetSpeed(int speed);

private:
	Gear m_gear = Gear::NeutralGear;
	bool m_engineIsOn = false;
	int m_speed = 0;
};