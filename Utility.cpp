#include "Utility.h"
#include <random>
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

Vector2D RandomPositionVector(const float lower_bound, const float upper_bound)
{
	return Vector2D(RandomFloat(lower_bound, upper_bound),
		RandomFloat(lower_bound, upper_bound));
}


Vector2D RandomPositionVector(const Vector2D& center, float radius)
{
	return Vector2D(RandomFloat(center.GetX() - radius, center.GetX() + radius),
		RandomFloat(center.GetY() - radius, center.GetY() + radius));
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