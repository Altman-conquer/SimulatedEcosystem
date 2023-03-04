#include "Grass.h"

Grass::Grass(shared_ptr<vector<shared_ptr<Animal>>> _environment):Animal(_environment)
{
	radius = 1.0;
}

Species Grass::GetSpecies()
{
	return Species::Grass;
}

void Grass::Update()
{
	radius += 0.5;
}

void Grass::Mutate()
{
	return;
}

void Grass::Breed()
{
	return;
}
