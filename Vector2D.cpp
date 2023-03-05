#include "Vector2D.h"
#include "Log.h"
//#include <math.h>

Vector2D::Vector2D() :Vector2D(0.0, 0.0) {}

Vector2D::Vector2D(float x, float y) :x(x), y(y) {}

Vector2D Vector2D::GetDirectionVector(Direction direction)
{
	switch (direction)
	{
	case Direction::Up:
		return Vector2D(0.0, 1.0);
	case Direction::Right:
		return Vector2D(1.0, 0.0);
	case Direction::Down:
		return Vector2D(0.0, -1.0);
	case Direction::Left:
		return Vector2D(-1.0, 0.0);
	default:
		Log::LogMessage("In function Vector2D::GetDirectionVector, direction is out of bounds", LogLevel::Error);
		return Vector2D(0.0, 0.0);
	}
}

float Vector2D::GetDistance(const Vector2D& vector1, const Vector2D& vector2)
{
	return sqrt(pow(vector1.x - vector2.x,2) + pow(vector1.y - vector2.y, 2));
}

float Vector2D::GetY()
{
	return y;
}

float Vector2D::GetLength() const
{
	return sqrt(x * x + y * y);
}

float Vector2D::GetX()
{
	return x;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
	return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
	return Vector2D(this->x - other.x, this->y - other.y);
}

Vector2D Vector2D::operator*(const float& other) const
{
	return Vector2D(this->x * other, this->y * other);
}

Vector2D Vector2D::operator/(const float& other) const
{
	if (other == 0.0)
		Log::LogMessage("In function Vector2D::operator/, other is 0", LogLevel::Error);
	return Vector2D(this->x / other, this->y / other);
}

std::ostream& operator<<(std::ostream& o, const Vector2D& other)
{
	o << other.x << ' ' << other.y << std::endl;
	return o;
}
