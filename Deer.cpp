#include "Deer.h"
#include "Utility.h"


Species Deer::GetSpecies()
{
	return Species::Deer;
}

void Deer::Move()
{
	float velocity_scalar = 0;

	if (this->stamina >= AnimalConstants::DEER_MAX_STAMINA / 2)
	{
		velocity_scalar = AnimalConstants::DEER_MAX_VELOCITY;
	}
	else if (this->stamina > AnimalConstants::DEER_MAX_STAMINA)
	{
		velocity_scalar = AnimalConstants::DEER_MAX_VELOCITY * (this->stamina * 2 / AnimalConstants::DEER_MAX_STAMINA);
	}
	else
	{
		velocity_scalar = AnimalConstants::DEER_MIN_VELOCITY;
	}


}

void Deer::Update()
{
	this->age_int += 1;
}

void Deer::Mutate()
{
	return;
}

void Deer::Breed()
{
	return;
}

bool Deer::Eat(Animal& other)
{
	if (Species::Grass == other.GetSpecies())
	{	
		this->energy += other.GetEnergy() * AnimalConstants::DEER_ENERGY_TRANSFORMATION_RATIO;
		return true;
	}
	else
	{
		return false;
	}
}

