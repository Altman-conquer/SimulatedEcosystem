#pragma once
#include "Utility.h"

class Vector2D {

public:

	Vector2D();

	Vector2D(int x, int y);

	static Vector2D GetDirectionVector(Direction direction);

	Vector2D operator+(const Vector2D& other)const;

	Vector2D operator-(const Vector2D& other)const;

private:

	int x;

	int y;
};


