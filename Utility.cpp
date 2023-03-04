#include "Utility.h"
#include<random>
#include<ctime>
#include "Vector2D.h"

int RandomInteger(int l, int r)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(l, r);
	return dis(gen);
}

Vector2D RandomUnitVector()
{
	return Vector2D::GetDirectionVector(Direction(RandomInteger(0, 3)));
}

void PrintAnimals(Environment environment)
{
	for (shared_ptr<Animal>& animal:*environment.GetEnvironment())
	{
		Log::LogMessage(std::to_string(animal->GetPosition().GetX())+ std::to_string(animal->GetPosition().GetY()), LogLevel::Info);
	}
}
