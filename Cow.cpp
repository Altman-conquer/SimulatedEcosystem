#include "Cow.h"

Species Cow::GetSpecies()
{
	return Species::Cow;
}

void Cow::Update()
{
	return;
}

Age Cow::GetAge()
{
	return Age(age_int >= AnimalConstants::COW_ADULT_AGE);
}

void Cow::Mutate()
{
	return;
}

void Cow::Breed()
{
	return;
}

void Cow::Move()
{
	return;
}

bool Cow::Eat(Animal& other)
{
	if (other.GetSpecies() != Species::Grass)
		return false;
	
}
