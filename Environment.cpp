#include "Environment.h"
#include "Tiger.h"
#include "Log.h"
#include "Grass.h"
#include "Cow.h"

namespace EnvironmentConstants {
	// Position limit of every dimension, assuming the environment is rectangular.
	const float UPPER_BOUND = 100.0;
	const float LOWER_BOUND = 0.0;
}


Environment::Environment(map<Species, int> _n)
{
	this->animals = std::make_shared<vector<shared_ptr<Animal>>>();
	for (auto& [species, number] : _n)
	{
		for (int i = 0; i < number; i++)
		{
			switch (species)
			{
			case Species::Grass:
				this->animals->push_back(std::make_shared<Grass>(this->animals));
				break;
			case Species::Cow:
				this->animals->push_back(std::make_shared<Cow>(this->animals));
				break;
				
			default:
				break;
			}
		}
	}
}

shared_ptr<vector<shared_ptr<Animal>>> Environment::GetEnvironment() const
{
	return animals;
}

bool Environment::AddSpecies(shared_ptr<Animal> new_animal)
{
	animals->push_back(new_animal);
	return true;
}

vector<int> Environment::GetDeadAnimals()
{
	vector<int> dead_animals;
	for (shared_ptr<Animal>& animal : *animals)
		if (prev_animals.count(animal->GetID()) == 0)
		{
			dead_animals.push_back(animal->GetID());
		}
	return dead_animals;
}

void Environment::Update()
{
	Log::LogMessage("The method or operation is not implemented.", LogLevel::Error);

	prev_animals.clear();
	for (shared_ptr<Animal>& animal : *animals)
		prev_animals.insert(animal->GetID());
	
	for (shared_ptr<Animal>& animal : *animals)
		animal->Update();
	
}

shared_ptr<Animal> Environment::GetClosetPair(const shared_ptr<vector<shared_ptr<Animal>>>& animals, const Animal& animal, Species species)
{
	shared_ptr<Animal> target=NULL;
	float min_distance=1e9;
	Vector2D position = animal.GetPosition();

	if (species != Species::NULLSPECIES) {
		
		for (shared_ptr<Animal>& neighbour: *animals)
			if (species==neighbour->GetSpecies()&&//belong to
				min_distance > Vector2D::GetDistance(neighbour->GetPosition(), position)&&//closest
				!(*neighbour==animal))//do not itself
			{//update
				min_distance = Vector2D::GetDistance(neighbour->GetPosition(), position);
				target = neighbour;
			}
	}
	else {
		for (shared_ptr<Animal>& neighbour : *animals)
			if (min_distance > Vector2D::GetDistance(neighbour->GetPosition(), position) &&//closest
				!(*neighbour == animal))//do not itself)
			{
				min_distance = Vector2D::GetDistance(neighbour->GetPosition(), position);
				target = neighbour;
			}
	}

	if (target == NULL)
		Log::LogMessage("Return value of Environment::GetClosetPair is NULL", LogLevel::Error);
	return target;
}

shared_ptr<Animal> Environment::GetClosetPair(const shared_ptr<vector<shared_ptr<Animal>>>& animals, const Animal& animal, std::set<Species> species)
{
	shared_ptr<Animal> target = NULL;
	float min_distance = 1e9;
	Vector2D position = animal.GetPosition();

	for (shared_ptr<Animal>& neighbour : *animals)
		if (species.count(neighbour->GetSpecies()) != 0 &&//belong to
			min_distance > Vector2D::GetDistance(neighbour->GetPosition(), position) &&//closest
			!(*neighbour == animal))//do not itself
		{//update
			min_distance = Vector2D::GetDistance(neighbour->GetPosition(), position);
			target = neighbour;
		}
	if (target == NULL)
		Log::LogMessage("Return value of Environment::GetClosetPair is NULL", LogLevel::Error);
	return target;
}

