#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <map>
#include "../Car/Car.h"

using SpeedLimit = std::pair<int, int>;

const std::map<int, SpeedLimit> GEAR_SPEED_LIMITS =
{
	{ -1, { 0, 20 } },
	{ 0, { 0, INT_MAX } },
	{ 1, { 0, 30 } },
	{ 2, { 20, 50 } },
	{ 3, { 30, 60 } },
	{ 4, { 40, 90 } },
	{ 5, { 50, 150 } },
};

TEST_CASE("Test engine turn on/off")
{
	Car car;
	car.TurnOnEngine();
	CHECK(car.IsTurnedOn());
	car.TurnOnEngine();
	CHECK(car.IsTurnedOn());

	car.SetGear(1);
	CHECK_THROWS_AS(car.TurnOffEngine(), std::runtime_error);
	car.SetSpeed(20);
	car.SetGear(0);
	CHECK_THROWS_AS(car.TurnOffEngine(), std::runtime_error);
	car.SetSpeed(0);
	car.TurnOffEngine();
	CHECK_FALSE(car.IsTurnedOn()); 
	car.TurnOffEngine(); 
	CHECK_FALSE(car.IsTurnedOn());
}

TEST_CASE("Test setting speed in 1-5 geer")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	CHECK(car.GetGear() == Gear::FirstGear);
	car.SetSpeed(25);
	CHECK(car.GetSpeed() == 25);

	car.SetGear(2);
	CHECK(car.GetGear() == Gear::SecondGear);
	car.SetSpeed(40);
	CHECK(car.GetSpeed() == 40);

	car.SetGear(3);
	CHECK(car.GetGear() == Gear::ThirdGear);
	car.SetSpeed(55);
	CHECK(car.GetSpeed() == 55);

	car.SetGear(4);
	CHECK(car.GetGear() == Gear::ForthGear);
	car.SetSpeed(79);
	CHECK(car.GetSpeed() == 79);

	car.SetGear(5);
	CHECK(car.GetGear() == Gear::FifthGear);
	car.SetSpeed(150);
	CHECK(car.GetSpeed() == 150);
}

TEST_CASE("Test correct of input values")
{
	Car car;
	car.TurnOnEngine();
	CHECK_THROWS_AS(car.SetGear(7), std::invalid_argument);
	car.SetGear(-1);
	CHECK_THROWS_AS(car.SetSpeed(-10), std::invalid_argument);
}

TEST_CASE("Test setting gear and speed with turning off engine")
{
	Car car;
	CHECK_FALSE(car.IsTurnedOn());
	car.SetGear(0);
	CHECK(car.GetGear() == Gear::NeutralGear);
	CHECK_THROWS_AS(car.SetGear(1), std::runtime_error);
	CHECK_THROWS_AS(car.SetSpeed(10), std::runtime_error);
}

TEST_CASE("Test setting speed in 0 gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(10);
	car.SetGear(0);
	CHECK(car.GetGear() == Gear::NeutralGear);
	car.SetSpeed(5);
	CHECK(car.GetSpeed() == 5);
	CHECK_THROWS_AS(car.SetSpeed(15), std::runtime_error);
}

TEST_CASE("Test reverse gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(11);
	CHECK_THROWS_AS(car.SetGear(-1), std::runtime_error);
	car.SetSpeed(0);
	car.SetGear(-1);
	CHECK(car.GetGear() == Gear::ReverseGear);
	car.SetSpeed(7);
	CHECK_THROWS_AS(car.SetGear(1), std::runtime_error);
	car.SetGear(0);
	CHECK_THROWS_AS(car.SetGear(1), std::runtime_error);
	car.SetSpeed(0);
	car.SetGear(1);
	CHECK(car.GetGear() == Gear::FirstGear);
}

TEST_CASE("Test changing gear with speed limit")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(1);
	car.SetSpeed(30);

	for (int i = 2; i < 6; i++)
	{
		car.SetGear(i);
		const auto [minSpeed, maxSpeed] = GEAR_SPEED_LIMITS.at(i);
		int middleGearSpeed = (minSpeed + maxSpeed) / 2;
		car.SetSpeed(middleGearSpeed);
		int minSpeedExtra = minSpeed - 1; 
		int maxSpeedExtra = maxSpeed + 1; 

		CHECK_NOTHROW(car.SetSpeed(minSpeed));
		CHECK_NOTHROW(car.SetSpeed(maxSpeed)); 

		CHECK_THROWS_AS(car.SetSpeed(minSpeedExtra), std::runtime_error); 
		CHECK_THROWS_AS(car.SetSpeed(maxSpeedExtra), std::runtime_error); 
	}
}

