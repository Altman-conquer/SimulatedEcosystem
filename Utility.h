#pragma once
#include<utility>
#include "Environment.h"

class Vector2D;

//************************************
// Method:    RandomInteger
// FullName:  RandomInteger
// Access:    public 
// Returns:   Uniformly generated integer value in range [l,r]
// Qualifier:
// Parameter: int l
// Parameter: int r
//************************************
int RandomInteger(int l, int r);

//************************************
// Method:    RandomUnitVector
// FullName:  RandomUnitVector
// Access:    public 
// Returns:   Random Vector2D
// Qualifier:
//************************************
Vector2D RandomUnitVector();

void PrintAnimals(Environment environment);
