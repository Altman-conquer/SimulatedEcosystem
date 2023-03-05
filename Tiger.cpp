#include "Tiger.h"
#include <memory>

Tiger::Tiger(std::shared_ptr<vector<shared_ptr<Animal>>> _environment) : Animal(_environment)
{
	position = RandomPositionVector();
}

Tiger::Tiger(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position) :Animal(_environment)
{
	position = _position;
}


Species Tiger::GetSpecies()
{
	return Species::Tiger;
}

void Tiger::Update()//behavior algorithm 
{
	//grow up
	age_int += 1;
	Log::LogMessage("Tiger update", LogLevel::Info);
	//check surrounding
	closest = Environment::GetClosetPair(environment, *this, Species::NULLSPECIES);
	float dis = Vector2D::GetDistance(this->GetPosition(), closest->GetPosition());

	if (closest->GetSpecies() == Species::Tiger)//same species
	{//check run or breed
		if (this->GetAge() == Age::Adult&&//adult
			closest->GetGender() != this->GetGender()&&//different gender
			dis < AnimalConstants::ADULT_DISTANCE * 2)//close to
		{//breed
			Breed();
		}
		else
		{//run away

		}
	} 
	else 
	{//check eatable

	}
}

Age Tiger::GetAge()
{
	return Age(this->age_int >= AnimalConstants::Tiger_ADULT_AGE);
}

void Tiger::Mutate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Tiger::Breed()
{
	if (RandomFloat(0.0, 1.0) > AnimalConstants::TIGER_BREED_PROBABILITY) 
	{//breed probability
		shared_ptr<Animal> female;
		if (this->gender == Gender::Male)
		{
			female = closest;
		}
		else
		{
			female = std::make_shared<Animal>(*this);
		}
		if (female->GetEnergy() > AnimalConstants::TIGER_STATE_ENERGY * 2)
		{//female check


			shared_ptr<Animal> new_animal = std::make_shared<Tiger>(this->environment,
				RandomPositionVector(position, AnimalConstants::BREED_RADIUS));
			this->environment->push_back(new_animal);
			Log::LogMessage("Tiger breed", LogLevel::Info);
		}
	}
}

void Tiger::Move()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Tiger::Eat(Animal& other)
{
	throw std::logic_error("The method or operation is not implemented.");
}
