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
