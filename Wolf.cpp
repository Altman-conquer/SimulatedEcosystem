#include "Wolf.h"

Wolf::Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Vector2D velocity, bool _isMale, map<Gene, float> _genes, float _stamina, float _energy) :Animal(_environment,  _position,velocity, _isMale,_genes, _stamina, _energy)
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
		return true;
	else return false;
}

void Wolf::Move() {
	
}

void Wolf::Update()
{
	age_int++;
}