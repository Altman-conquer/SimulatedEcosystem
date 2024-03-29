#pragma once
#include <iostream>


enum class Direction {
	Up,
	Right,
	Down,
	Left
};

class Vector2D {

	friend std::ostream& operator<<(std::ostream& o, const Vector2D& other);
	
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

	float GetX() const;
	
	float GetY() const;

	float GetLength() const;

	//************************************
	// Method:    GetNormalized
	// FullName:  Vector2D::GetNormalized
	// Access:    public 
	// Returns:   Normalized Vector2D(unit vector)
	// Qualifier: const
	//************************************
	Vector2D GetNormalized() const;


	//************************************
	// Method:    GetDistance
	// FullName:  Vector2D::GetDistance
	// Access:    public static 
	// Returns:   float
	// Qualifier:
	// Parameter: const Vector2D & vector1
	// Parameter: const Vector2D & vector2
	// it is used to calculate the Euler distance between two animal 
	//************************************
	static float GetDistance(const Vector2D& vector1, const Vector2D& vector2);

	void ClipBound(float lower_bound, float upper_bound);

	Vector2D operator+(const Vector2D& other)const;

	Vector2D operator-(const Vector2D& other)const;

	Vector2D operator*(const float& other)const;

	Vector2D operator/(const float& other)const;


	

private:

	float x;

	float y;
};

std::ostream& operator<<(std::ostream& o,const Vector2D& other);