#include "Cow.h"

Cow::Cow(shared_ptr<vector<shared_ptr<Animal>>> _environment) :Animal(_environment)
{
	position = RandomPositionVector();
}

Cow::Cow(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position) :Animal(_environment)
{
	position = _position;
}

Species Cow::GetSpecies()
{
	return Species::Cow;
}

void Cow::Update()
{
	Move();
	Breed();
	if (energy <= 0.0)
		Die();
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
	if (GetAge() == Age::Child || RandomFloat(0.0, 1.0) > AnimalConstants::GRASS_BREED_PROBABILITY)
		return;

	shared_ptr<Animal> other = Environment::GetClosetPair(environment, *this, Species::Cow);
	if (other->GetGender() != gender)
	{
		shared_ptr<Animal> new_animal = 
			std::make_shared<Cow>(this->environment, RandomPositionVector(position, AnimalConstants::BREED_RADIUS));
		this->environment->push_back(new_animal);
	}
}

void Cow::Move()
{
	shared_ptr<Animal> other = Environment::GetClosetPair(environment, *this, Species::NULLSPECIES);
	Vector2D direction;
	float distance = (position - other->GetPosition()).GetLength();
	if (distance > AnimalConstants::COW_PROB_RADIUS)// Idle
	{
		
	}
	else
	{
		if (other->GetSpecies() == Species::Grass)
		{
			if(Eat(*other))
			direction = (other->GetPosition() - position).GetNormalized();
			
		}
		else if (other->GetSpecies() == Species::Tiger || other->GetSpecies() == Species::Wolf)
			direction = (position - other->GetPosition()).GetNormalized();
	}
	
	float velocity_scalar = 0;
	/*
	if (this->stamina >= AnimalConstants::COW_MAX_STAMINA / 2)
		velocity_scalar = AnimalConstants::COW_MAX_VELOCITY;
	else if (this->stamina > AnimalConstants::COW_MAX_STAMINA)
		velocity_scalar = AnimalConstants::COW_MAX_VELOCITY * (this->stamina * 2 / AnimalConstants::COW_MAX_STAMINA);
	else
		velocity_scalar = AnimalConstants::COW_MIN_VELOCITY;*/

}

bool Cow::Eat(Animal& other)
{
	if (other.GetSpecies() != Species::Grass)
		return false;
	if ((other.GetPosition() - position).GetLength() <= GetCollisionRadius())
	{
		energy += other.GetEnergy();
		other.Die();
		return true;
	}
	return false;
}
