#include "Vector.h"
#include "Log.h"

Vector::Vector() :Vector(0, 0) {}

Vector::Vector(int x, int y) :x(x), y(y) {}

Vector Vector::GetDirectionVector(Direction direction)
{
	switch (direction)
	{
	case Direction::Up:
		return Vector(0, 1);
	case Direction::Right:
		return Vector(1, 0);
	case Direction::Down:
		return Vector(0, -1);
	case Direction::Left:
		return Vector(-1, 0);
	default:
		Log::LogMessage<std::string>("In function Vector::GetDirectionVector, direction is out of bounds", LogLevel::Error);
		return Vector(0, 0);
	}
}

Vector Vector::operator+(const Vector& other) const
{
	return Vector(this->x + other.x, this->y + other.y);
}

Vector Vector::operator-(const Vector& other) const
{
	return Vector(this->x - other.x, this->y - other.y);
}
