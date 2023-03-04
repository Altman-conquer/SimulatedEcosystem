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

float RandomFloat(float l, float r)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(l, r);
	return dis(gen);
}

Vector2D RandomUnitVector()
{
	return Vector2D::GetDirectionVector(Direction(RandomInteger(0, 3)));
}
