#include "Animal.h"

int Animal::animalCount = 0;

namespace AnimalConstants {

	// Age limits of animals to tell it is adult or not.
	const int COW_ADULT_AGE = 50;

	const int GRASS_ADULT_AGE = 10;

	// Max age of animals
	const int COW_MAX_AGE = 100;

	const float GRASS_INITIAL_RADIUS = 1.0;

	const float GRASS_GROWTH_SPEED = 1.0; // radius += GRASS_GROWTH_SPEED;

	// Breed probability of animals
	const float GRASS_BREED_PROBABILITY = 0.1;

	// Size of picture of the adult and child animal
	const int SIZE_OF_CHILD = 50;
	const int SIZE_OF_ADULT = 100;
}

Animal::Animal(std::shared_ptr<vector<shared_ptr<Animal>>> _environment):id(Animal::animalCount++),age_int(0)
{
	this->environment = _environment;
}

Vector2D Animal::GetPosition() 
{
	return position;
}


Animal::Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
	Vector2D velocity, bool _isMale, map<Gene, float> _genes, float _stamina, float _energy):Animal(_environment)
{
	this->position = _position;
	this->velocity = velocity;
	this->is_male = _isMale;
	this->genes = _genes;
	this->stamina = _stamina;
	this->energy = _energy;
}

Animal::~Animal(){}


bool Animal::operator==(const Animal& other) const
{
	return id == other.id;
}

