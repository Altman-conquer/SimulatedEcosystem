#include "Grass.h"
#include "Utility.h"
#include <memory>
#include "Animal.h"

Grass::Grass(shared_ptr<vector<shared_ptr<Animal>>> _environment):Animal(_environment)
{
	position = RandomPositionVector();
}

Grass::Grass(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position):Animal(_environment)
{
	position = _position;
}

Species Grass::GetSpecies()
{
	return Species::Grass;
}

void Grass::Update()
{
	if (isDead) return;
	age_int += 1;
	energy += AnimalConstants::GRASS_RECOVER_SPEED;
	Breed();
}

Age Grass::GetAge()
{
	return Age(this->age_int >= AnimalConstants:: ADULT_AGE[int(Species::Grass)]);
}

void Grass::Mutate()
{
	return;
}

void Grass::Breed()
{	
	if (isDead) return;
	if (GetAge() == Age::Child)
		return;
	if (RandomFloat(0.0, 1.0) < AnimalConstants::BREED_PROBABILITY[int(Species::Grass)])
	{
		shared_ptr<Animal> new_animal = std::make_shared<Grass>(this->environment, RandomPositionVector(position, AnimalConstants::BREED_RADIUS));
		this->environment->push_back(new_animal);
	}
}

void Grass::Move()
{
	return;
}

bool Grass::Eat(Animal& other)
{
	return false;
}

QString Grass::GetPicturePath() {
	return ":/sourcePicture/grass.png";
}