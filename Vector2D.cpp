#include "Vector2D.h"
#include "Log.h"

Vector2D::Vector2D() :Vector2D(0, 0) {}

Vector2D::Vector2D(int x, int y) :x(x), y(y) {}

Vector2D Vector2D::GetDirectionVector(Direction direction)
{
	switch (direction)
	{
	case Direction::Up:
		return Vector2D(0, 1);
	case Direction::Right:
		return Vector2D(1, 0);
	case Direction::Down:
		return Vector2D(0, -1);
	case Direction::Left:
		return Vector2D(-1, 0);
	default:
		Log::LogMessage("In function Vector2D::GetDirectionVector, direction is out of bounds", LogLevel::Error);
		return Vector2D(0, 0);
	}
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	return Vector2D(this->x - other.x, this->y - other.y);
}
