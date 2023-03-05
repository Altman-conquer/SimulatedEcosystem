#include "Animal.h"
#include "Vector2D.h"

int Animal::animalCount = 0;

namespace AnimalConstants {

	// Age limits of animals to tell it is adult or not.
	const int COW_ADULT_AGE = 50;

	const int GRASS_ADULT_AGE = 10;

	const int Deer_ADULT_AGE = 50;

	// Max age of animals
	const int COW_MAX_AGE = 100;

	const float GRASS_INITIAL_RADIUS = 1.0;

	const float GRASS_GROWTH_SPEED = 1.0; // radius += GRASS_GROWTH_SPEED;

	const int Deer_MAX_AGE = 100;


	// Breed probability of animals
	const float GRASS_BREED_PROBABILITY = 0.1;

}

Animal::Animal(std::shared_ptr<vector<shared_ptr<Animal>>> _environment):id(Animal::animalCount++),age_int(0)
{
	this->environment = _environment;
}

float Animal::GetEnergy()
{
	return energy;
}

Vector2D Animal::GetPosition() const
{
	return position;
}


Vector2D Animal::GetDirection() const
{
	return velocity/velocity.GetLength();
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

