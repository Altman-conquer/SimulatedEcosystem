#include "Utility.h"
#include<random>
#include<ctime>
#include "Animal.h"
#include "Vector2D.h"
#include "Environment.h"

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

Vector2D RandomPositionVector()
{
	return Vector2D(RandomFloat(EnvironmentConstants::LOWER_BOUND, EnvironmentConstants::UPPER_BOUND),
		RandomFloat(EnvironmentConstants::LOWER_BOUND, EnvironmentConstants::UPPER_BOUND));
}


Vector2D RandomPositionVector(const Vector2D& center, float radius)
{
	return Vector2D(RandomFloat(center.GetX() - radius, center.GetX() + radius),
		RandomFloat(center.GetY() - radius, center.GetY() + radius));
}


void PrintAnimals(const Environment& environment)
{
	for (shared_ptr<Animal>& animal:*environment.GetEnvironment())
	{
		Log::LogMessage(std::to_string(animal->GetPosition().GetX()) + "  " + std::to_string(animal->GetPosition().GetY()), LogLevel::Info);
	}
}

void* MemoryCopy(void* destination, const void* source, size_t num)
{
	if (destination == nullptr || source == nullptr)
		return destination;
	char* des = static_cast<char*>(destination);
	const char* src = static_cast<const char*>(source);
	while (num--) // No considering memory overlap
		*des++ = *src++;
	return destination;
}