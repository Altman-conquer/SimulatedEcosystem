#include "Animal.h"
#include "Vector2D.h"

int Animal::animalCount = 0;

namespace AnimalConstants {

	// Age limits of animals to tell it is adult or not.
	const int COW_ADULT_AGE = 50;

	const int GRASS_ADULT_AGE = 10;

	const int Deer_ADULT_AGE = 50;

	const int WOLF_ADULT_AGE=60;


	// Max age of animals
	const int COW_MAX_AGE = 100;

	const int Deer_MAX_AGE = 100;

	const int WOLF_MAX_AGE=120;


	// Breed probability of animals
	const float GRASS_BREED_PROBABILITY = 0.1;

	const float GRASS_BREED_RADIUS = 10.0;

	// Size of picture of the adult and child animal
	const int SIZE_OF_CHILD = 50;
	const int SIZE_OF_ADULT = 100;
  
	//Max stamina of animals
	const float DEER_MAX_STAMINA = 1.0;

	const float WOLF_MAX_STAMINA = 100;

	//Min stamina of animals
	const float DEER_MIN_STAMINA = 1.0;

	const float WOLF_MIN_STAMINA = 1.0;

	//Max velocity of animals
	const float DEER_MAX_VELOCITY = 50.0;

	const float WOLF_MAX_VELOCITY = 60;

	//Min velocity of animals
	const float DEER_MIN_VELOCITY = 1.0;

	const float WOLF_MIN_VELOCITY = 1.0;

	//Energy transformation ratio
	const float DEER_ENERGY_TRANSFORMATION_RATIO = 0.8;

	//Energy consume ratio
	const float DEER_CONSUME_ENERGY_RATIO = 1.0;

	//recover stamina ratio
	const float DEER_RECOVER_STAMINA_RATIO = 1.0;

	//probe radius of animals
	const float DEER_PROBE_Radius = 1.0;

	const float GRASS_RECOVER_SPEED = 0.5;

	const float WOLF_ENERGY_TRANSFORMATION_RATIO = 0.3;
}

Animal::Animal(std::shared_ptr<vector<shared_ptr<Animal>>> _environment):
	id(Animal::animalCount++),age_int(0),environment(_environment),energy(0),gender(Gender::Male),stamina(0)
{

}

Gender Animal::GetGender()
{
	return gender;
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

bool Animal::Die()
{
	// remove self from environment
	for (auto it = environment->begin(); it != environment->end(); it++)
	{
		if ((*it)->GetID() == id)
		{
			environment->erase(it);
			return true;
		}
	}
	return false;
}

Animal::Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
	Vector2D _velocity, Gender _gender, map<Gene, float> _genes, float _stamina, float _energy):
	id(Animal::animalCount++), age_int(0),environment(_environment), position(_position),
	velocity(_velocity), gender(_gender), genes(_genes), stamina(_stamina), energy(_energy)
{}

Animal::~Animal(){}


int Animal::GetID()
{
	return id;
}

bool Animal::operator==(const Animal& other) const
{
	return id == other.id;
}

