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
	const float CHILD_DISTANCE = 3;
	const float ADULT_DISTANCE = 5;

	//probe radius of animals
	const float PROBE_RADIUS = 10.0;

	// Age limits of animals to tell it is adult or not.
	const int ADULT_AGE[int(Species::NULLSPECIES)] = { 10.0,10.0,10,10,10 };

	// Max age of animals
	 const int MAX_AGE[int(Species::NULLSPECIES)] = { 0,60,60,60,60 };

	// Breed probability of animals
	 const float BREED_PROBABILITY[int(Species::NULLSPECIES)] = { .5,.5,.5,.5,.3 };

	//Max stamina of animals
	 const float MAX_STAMINA[int(Species::NULLSPECIES)] = { 0,10.0,10.0,10.0,10.0 };
	 
	//Min stamina of animals
	 const float MIN_STAMINA[int(Species::NULLSPECIES)] = { 0,1.0,1.0,1.0,1.0 };

	//Max velocity of animals
	 const float MAX_VELOCITY[int(Species::NULLSPECIES)] = { 0,50.0,50.0,50.0,50.0 };
	 
	//Min velocity of animals
	 const float MIN_VELOCITY[int(Species::NULLSPECIES)] = { 0,1.0,1.0,1.0,1.0 };

	// The stating energy
	 const float INITIAL_ENERGY[int(Species::NULLSPECIES)] = { 100.0,100.0,100.0,100.0,100.0 };
	 
	//Energy transformation ratio
	const float ENERGY_TRANSFORMATION_RATIO[int(Species::NULLSPECIES)] = { 0,1.0,1.0,1.0,.8 };

	// the energy of grass will increase every tick
	 const float GRASS_RECOVER_SPEED = 1.0;

	//Energy consume ratio
	 const float CONSUME_ENERGY_RATIO[int(Species::NULLSPECIES)] = { 0,1,1,1,1 };

	//recover stamina ratio
	 const float RECOVER_STAMINA_RATIO[int(Species::NULLSPECIES)] = { 0,1,1,1,1 };

	//consume stamina ratio
	 const float CONSUME_STAMINA_RATIO[int(Species::NULLSPECIES)] = { 0,1,1,1,1 };

	//Idle probability of animals
	 const float IDLE_PROBABILITY[int(Species::NULLSPECIES)] = { 0,.2,.2,.2,.2 };

	//Max energy of animals
	 const float MAX_ENERGY[int(Species::NULLSPECIES)] = { 0,100,100,100,100 };

	 const float MIN_ENERGY[int(Species::NULLSPECIES)] = { 0,10,10,10,10 };

	 const float INITIAL_HEALTH[int(Species::NULLSPECIES)] = { 20,100,100,100,100 };
	 
	 const float DAMAGE[int(Species::NULLSPECIES)] = { 10.0,10.0,10.0,10.0,10.0 };

}

Animal::Animal(std::shared_ptr<vector<shared_ptr<Animal>>> _environment):
	id(Animal::animalCount++),age_int(0),environment(_environment),energy(0),gender(Gender(RandomInteger(0,1))),stamina(0), isDead(false),health(0)
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

