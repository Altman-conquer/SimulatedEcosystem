#include "Deer.h"
#include "Utility.h"


Species Deer::GetSpecies()
{
	return Species::Deer;
}

void Deer::Move()
{
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
		return true;
	}
	else
		return false;
}

