#include "Animal.h"

Animal::Animal(std::shared_ptr<vector<shared_ptr<Animal>>> _environment)
{
	this->environment = _environment;
}
//12332
Vector2D Animal::GetPosition()
{
	return position;
}