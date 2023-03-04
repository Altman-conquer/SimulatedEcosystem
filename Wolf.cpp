#include "Wolf.h"

Wolf::Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment) :Animal(_environment)
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