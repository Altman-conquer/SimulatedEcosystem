#include "Animal.h"
#include "Vector2D.h"
#include <utility>
#include "Log.h"
#include"AVLTree.h"


int Animal::animalCount = 0;

namespace AnimalConstants { 

	//Breed radius
	 const float BREED_RADIUS = 10.0;

	// The distance of crash
	const float CHILD_DISTANCE = 10;
	const float ADULT_DISTANCE = 30;

	// Age limits of animals to tell it is adult or not.
	 const int GRASS_ADULT_AGE = 10.0;
	 const int COW_ADULT_AGE = 10.0;
	 const int DEER_ADULT_AGE = 10.0;
	 const int WOLF_ADULT_AGE = 10.0;
	 const int TIGER_ADULT_AGE = 10.0;

	// Max age of animals
	 const int COW_MAX_AGE = 60.0;
	 const int DEER_MAX_AGE = 60.0;
	 const int WOLF_MAX_AGE = 60.0;
	 const int TIGER_MAX_AGE = 60.0;

	// Breed probability of animals
	 const float GRASS_BREED_PROBABILITY = 1.0;
	 const float COW_BREED_PROBABILITY = 1.0;
	 const float TIGER_BREED_PROBABILITY = 0.3;
	 const float DEER_BREED_PROBABILITY = 1.0;
	 const float WOLF_BREED_PROBABILITY = 1.0;
  
	//Max stamina of animals
	 const float COW_MAX_STAMINA = 1.0;
	 const float DEER_MAX_STAMINA = 1.0;
	 const float WOLF_MAX_STAMINA = 1.0;
	 const float TIGER_MAX_STAMINA = 1.0;

	//Min stamina of animals
	 const float COW_MIN_STAMINA = 1.0;
	 const float DEER_MIN_STAMINA = 1.0;
	 const float WOLF_MIN_STAMINA = 1.0;
	 const float TIGER_MIN_STAMINA = 1.0;



	//Max velocity of animals
	 const float COW_MAX_VELOCITY = 1.0;
	 const float DEER_MAX_VELOCITY = 1.0;
	 const float WOLF_MAX_VELOCITY = 1.0;
	 const float TIGER_MAX_VELOCITY = 1.0;

	//Min velocity of animals
	 const float COW_MIN_VELOCITY = 1.0;
	 const float DEER_MIN_VELOCITY = 1.0;
	 const float WOLF_MIN_VELOCITY = 1.0;
	 const float TIGER_MIN_VELOCITY = 1.0;

	// The stating energy
	const float TIGER_INITIAL_ENERGY=100.0;
	const float GRASS_INITIAL_ENERGY = 100.0;
	const float COW_INITIAL_ENERGY = 100.0;
	const float DEER_INITIAL_ENERGY = 100.0;
	const float WOLF_INITIAL_ENERGY = 100.0;

	//Energy transformation ratio
	 const float COW_ENERGY_TRANSFORMATION_RATIO = 1.0;
	 const float DEER_ENERGY_TRANSFORMATION_RATIO = 1.0;
	 const float WOLF_ENERGY_TRANSFORMATION_RATIO = 1.0;
	 const float TIGER_ENERGY_TRANSFORMATION_RATIO = 0.8;

	// the energy of grass will increase every tick
	 const float GRASS_RECOVER_SPEED = 1.0;

	//Energy consume ratio
	 const float COW_CONSUME_ENERGY_RATIO = 1.0;
	 const float DEER_CONSUME_ENERGY_RATIO = 1.0;
	 const float WOLF_CONSUME_ENERGY_RATIO = 1.0;
	 const float TIGER_CONSUME_ENERGY_RATIO = 1.0;

	//recover stamina ratio
	 const float COW_RECOVER_STAMINA_RATIO = 1.0;
	 const float DEER_RECOVER_STAMINA_RATIO = 1.0;
	 const float WOLF_RECOVER_STAMINA_RATIO = 1.0;
	 const float TIGER_RECOVER_STAMINA_RATIO = 1.0;

	//consume stamina ratio
	 const float COW_CONSUME_STAMINA_RATIO = 1.0;
	 const float DEER_CONSUME_STAMINA_RATIO = 1.0;
	 const float WOLF_CONSUME_STAMINA_RATIO = 1.0;
	 const float TIGER_CONSUME_STAMINA_RATIO = 1.0;


	//probe radius of animals
	 const float PROBE_RADIUS = 1.0;

	//Idle probability of animals
	 const float DEER_IDLE_PROBABILITY = 0.5;
	 const float COW_IDLE_PROBABILITY = 0.5;
	 const float WOLF_IDLE_PROBABILITY = 0.5;
	 const float TIGER_IDLE_PROBABILITY = 0.5;

	//Max energy of animals
	 const float COW_MAX_ENERGY = 1.0;
	 const float DEER_MAX_ENERGY = 1.0;
	 const float WOLF_MAX_ENERGY = 1.0;
	 const float TIGER_MAX_ENERGY = 1.0;

	 const float COW_MIN_ENERGY = 10.0;
	 const float DEER_MIN_ENERGY = 10.0;
	 const float WOLF_MIN_ENERGY = 10.0;
	 const float TIGER_MIN_ENERGY = 10.0;

	 
	 const float COW_DAMAGE = 1.0;
	 const float DEER_DAMAGE = 1.0;
	 const float WOLF_DAMAGE = 1.0;
	 const float TIGER_DAMAGE = 1.0;

}

Animal::Animal(std::shared_ptr<vector<shared_ptr<Animal>>> _environment):
	id(Animal::animalCount++),age_int(0),environment(_environment),energy(0),gender(Gender(RandomInteger(0,1))),stamina(0)
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


bool Animal::DecreaseEnergy(float value)
{
	energy -= value;
	energy = std::max(energy, 0.0f);
	return true;
}

Vector2D Animal::GetPosition() const
{
	return position;
}


Vector2D Animal::GetDirection() const
{
	return velocity/velocity.GetLength();
}

float Animal::GetCollisionRadius()
{
	if (GetAge() == Age::Child)
		return AnimalConstants::CHILD_DISTANCE;
	else
		return AnimalConstants::ADULT_DISTANCE;
}

bool Animal::operator!=(const Animal& other) const
{
	return this->id != other.id;
}


Vector2D Animal::GetPrevPosition() const
{
	return prev_position;
}

bool Animal::Die()
{
	// remove self from environment
	for (auto it = environment->begin(); it != environment->end(); it++)
	{
		if ((*it)->GetID() == id)
		{
			environment->erase(it);
			isDead = true;
			return true;
		}
	}
	return false;
}

bool Animal::Hurt(float damage)
{
	health -= damage;
	if (health <= 0)
		return false;
	return true;
}

Animal::Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
	Vector2D _velocity, Gender _gender, AVLTree<Gene, float> _genes, float _stamina, float _energy):
	id(Animal::animalCount++), age_int(0),environment(_environment), position(_position), prev_position(_position),
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

