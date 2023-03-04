#include "Animal.h"

int Animal::animalCount = 0;


Animal::Animal(std::shared_ptr<vector<shared_ptr<Animal>>> _environment):id(Animal::animalCount++)
{
	this->environment = _environment;
}
//12332
//sadsad
Vector2D Animal::GetPosition()
{
	return position;
}


Animal::Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Vector2D velocity, bool _isMale, map<Gene, float> _genes):Animal(_environment)
{
	this->position = _position;
	this->velocity = velocity;
	this->is_male = _isMale;
	this->genes = _genes;
}

Animal::~Animal(){}


bool Animal::operator==(const Animal& other) const
{
	return id == other.id;
}

