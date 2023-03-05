#include "Tiger.h"
#include "Vector2D.h"

Tiger::Tiger(std::shared_ptr<vector<shared_ptr<Animal>>> _environment) : Animal(_environment)
{
	
}

Species Tiger::GetSpecies()
{
	return Species::Tiger;
}

void Tiger::Update()
{
	Log::LogMessage("Tiger update", LogLevel::Info);
	Breed();
	
}

void Tiger::Mutate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Tiger::Breed()
{
	shared_ptr<Animal> closest =Environment:: GetClosetPair(environment,*this,Species::NULLSPECIES);
	float distance=GetDistance()
	Log::LogMessage("Tiger breed", LogLevel::Info);

}

void Tiger::Move()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Tiger::Eat(Animal& other)
{
	throw std::logic_error("The method or operation is not implemented.");
}
