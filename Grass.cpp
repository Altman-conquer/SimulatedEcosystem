#include "Grass.h"

Grass::Grass(shared_ptr<vector<shared_ptr<Animal>>> _environment):Animal(_environment)
{
	radius = AnimalConstants::GRASS_INITIAL_RADIUS;
}

Species Grass::GetSpecies()
{
	return Species::Grass;
}

void Grass::Update()
{
	radius += AnimalConstants::GRASS_GROWTH_SPEED;
}

void Grass::Mutate()
{
	return;
}

void Grass::Breed()
{
	return;
}
