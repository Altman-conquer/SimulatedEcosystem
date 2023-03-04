#include "Deer.h"
#include "Utility.h"

Deer::Deer(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Vector2D velocity,
bool _isMale, map<Gene, float> _genes, float _stamina, float _energy)
	:Animal(_environment,_position, velocity, _isMale, _genes,_stamina,_energy)
{
}

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

