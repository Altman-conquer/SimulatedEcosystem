#include "Wolf.h"

Wolf::Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
	Vector2D _velocity, Gender _gender, map<Gene, float> _genes, float _stamina, float _energy) :Animal(_environment, _position,
		_velocity, _gender, _genes, _stamina, _energy)
{
}


Species Wolf::GetSpecies()
{
	return Species::Wolf;
}

void Wolf::Mutate()
{
	Log::LogMessage("The method or operation is not implemented.", LogLevel::Error);
}

void Wolf::Breed()
{
	Log::LogMessage("The method or operation is not implemented.", LogLevel::Error);
}

bool Wolf::Eat(Animal& other) 
{
	if (other.GetSpecies() == Species::Cow || other.GetSpecies() == Species::Deer)
	{	
		energy += AnimalConstants::WOLF_ENERGY_TRANSFORMATION_RATIO* other.GetEnergy();
		return true;
	}
	else return false;
}

void Wolf::Move()
{
	State state;
	Vector2D presentPosition = this->position;

	shared_ptr<Animal> target1 = Environment::GetClosetPair(this->environment, *this, Species::Cow);
	Vector2D position1 = target1->GetPosition();
	int d1 = Vector2D::GetDistance(position1, presentPosition);
	
	shared_ptr<Animal> target2 = Environment::GetClosetPair(this->environment, *this, Species::Deer);
	Vector2D position2 = target2->GetPosition();
	int d2 = Vector2D::GetDistance(position2,presentPosition);

	//move toward cow
	if (d1 < d2&&d1<= AnimalConstants::WOLF_PROBE_DISTANCE)
	{
		if (stamina >= AnimalConstants::WOLF_MIN_STAMINA)
		{
			state = State::Run;
			this->velocity=AnimalConstants
		}
	}

	//move toward deer
	else if(d1 >= d2 && d2 <= AnimalConstants::WOLF_PROBE_DISTANCE)
	{

	}
	else 
	{

	}
}

void Wolf::Update()
{
	age_int++;
}

Age Wolf::GetAge()
{
	return Age(this->age_int >= AnimalConstants::WOLF_ADULT_AGE);
}