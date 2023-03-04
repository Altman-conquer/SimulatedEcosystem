#pragma once
#include "Utility.h"


enum class Direction {
	Up,
	Right,
	Down,
	Left
};

class Vector2D {

public:

	Vector2D();

	Vector2D(float x, float y);

	//************************************
	// Method:    GetDirectionVector
	// FullName:  Vector2D::GetDirectionVector
	// Access:    public static 
	// Returns:   Vector2D. A unit vector
	// Qualifier:
	// Parameter: Direction direction
	//************************************
	static Vector2D GetDirectionVector(Direction direction);

	Vector2D operator+(const Vector2D& other)const;

	Vector2D operator-(const Vector2D& other)const;

	Vector2D operator*(const float& other)const;

	Vector2D operator/(const float& other)const;

private:

	float x;

	float y;
};


