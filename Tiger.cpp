#include "Tiger.h"

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

void Tiger::Update()
{
	age_int += 1;
	Log::LogMessage("Tiger update", LogLevel::Info);
	if(this->GetAge()==Age::Adult) Breed();
	
}

void Tiger::Mutate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Tiger::Breed()
{
	shared_ptr<Animal> closest = Environment::GetClosetPair(environment, *this, Species::NULLSPECIES);
	if (closest->GetSpecies()==Species::Tiger//same species
		&&closest->GetAge()==Age::Adult//adult
		&&closest->GetGender()!=this->GetGender())//different gender
	{
		float dis = Vector2D::GetDistance(this->GetPosition(), closest->GetPosition());
		if (dis<AnimalConstants::ADULT_DISTANCE*2)//close to
		{//get broth to 
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
