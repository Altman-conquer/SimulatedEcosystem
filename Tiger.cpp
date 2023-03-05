#include "Tiger.h"

Tiger::Tiger(std::shared_ptr<vector<shared_ptr<Animal>>> _environment) : Animal(_environment)
{
	
}

Species Tiger::GetSpecies()
{
	return Species::Tiger;
}

void Tiger::Update()
{
	Log::LogMessage("The method or operation is not implemented.", LogLevel::Error);
}

void Tiger::Mutate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Tiger::Breed()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Tiger::Move()
{
	throw std::logic_error("The method or operation is not implemented.");
}

bool Tiger::Eat(Animal& other)
{
	throw std::logic_error("The method or operation is not implemented.");
}
