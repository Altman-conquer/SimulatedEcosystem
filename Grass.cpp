#include "Grass.h"

Grass::Grass(shared_ptr<vector<shared_ptr<Animal>>> _environment):Animal(_environment)
{
	radius = AnimalConstants::GRASS_INITIAL_RADIUS;
	position = 
}

Species Grass::GetSpecies()
{
	return Species::Grass;
}

void Grass::Update()
{
	radius += AnimalConstants::GRASS_GROWTH_SPEED;
}

Age Grass::GetAge()
{
	return Age(this->age_int >= AnimalConstants::GRASS_ADULT_AGE);
}

void Grass::Mutate()
{
	return;
}

void Grass::Breed()
{
	return;
}

void Grass::Move()
{
	return;
}

bool Grass::Eat(Animal& other)
{
	return false;
}
