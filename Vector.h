#pragma once
#include "Utility.h"

class Vector {

public:

	Vector();

	Vector(int x, int y);

	static Vector GetDirectionVector(Direction direction);

	Vector operator+(const Vector& other)const;

	Vector operator-(const Vector& other)const;

private:

	int x;

	int y;
};


