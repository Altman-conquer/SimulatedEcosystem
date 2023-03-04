#pragma once
#include<utility>

class Vector2D;
class Environment;

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
// Method:    RandomFloat
// FullName:  RandomFloat
// Access:    public 
// Returns:   Random float in range [l,r]
// Qualifier:
// Parameter: float l
// Parameter: float r
//************************************
float RandomFloat(float l, float r);

//************************************
// Method:    RandomUnitVector
// FullName:  RandomUnitVector
// Access:    public 
// Returns:   Random Vector2D
// Qualifier:
//************************************
Vector2D RandomUnitVector();

//************************************
// Method:    RandomVector
// FullName:  RandomVector
// Access:    public 
// Returns:   Random position vector in the environment
// Qualifier:
//************************************
Vector2D RandomVector();

void PrintAnimals(Environment environment);
