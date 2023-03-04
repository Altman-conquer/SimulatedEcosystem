#include "Animal.h"

Animal::Animal(std::shared_ptr<vector<shared_ptr<Animal>>> _environment)
{
	this->environment = _environment;
}

Animal::Animal() {

}

Vector2D Animal::GetPosition()
{
	return position;
}