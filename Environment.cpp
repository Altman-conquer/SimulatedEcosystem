#include "Environment.h"
#include "Tiger.h"
#include "Log.h"
#include "Grass.h"
#include "Cow.h"
#include "Wolf.h"

namespace EnvironmentConstants {
	// Position limit of every dimension, assuming the environment is rectangular.
	const float UPPER_BOUND = 800;
	const float LOWER_BOUND = 0;
	const float UPDATE_FREQUENCY_MS = 500;
}




Environment::Environment(AVLTree<Species, int> _n)
{
	this->animals = std::make_shared<vector<shared_ptr<Animal>>>();
	for (auto& data: _n)
	{
		Species& species = data.data.first;
		int& num = data.data.second;
		for (int i = 0; i < num; i++)
		{
			switch (species)
			{
			case Species::Grass:
				this->animals->push_back(std::make_shared<Grass>(this->animals));
				break;
			case Species::Cow:
				this->animals->push_back(std::make_shared<Cow>(this->animals));
				break;
			case Species::Deer:
				this->animals->push_back(std::make_shared<Cow>(this->animals));
				break;
			case Species::Wolf:
				this->animals->push_back(std::make_shared<Wolf>(this->animals));
				break;
			case Species::Tiger:
				this->animals->push_back(std::make_shared<Tiger>(this->animals));
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
	//PRINT_FUNCTION_NAME(LogLevel::Info);
	DETAIL_LOG("Update Environment", LogLevel::Info);

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
		Log::LogMessage("Return value of Environment::GetClosetPair is NULL", LogLevel::Warning);
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
		Log::LogMessage("Return value of Environment::GetClosetPair is NULL", LogLevel::Warning);
	return target;
}

