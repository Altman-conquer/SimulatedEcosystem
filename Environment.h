#pragma once
#include <memory>
#include "AVLTree.h"
#include "DynamicArrayList.h"
#include "Vector2D.h"
#include "Animal.h"
#include <set>
#include <vector>

class Animal;
enum class Species;

using std::vector;
using std::shared_ptr;

namespace EnvironmentConstants{
	// Position limit of every dimension, assuming the environment is rectangular.
	extern const float UPPER_BOUND;
	extern const float LOWER_BOUND;
	extern const float UPDATE_FREQUENCY_MS; // Eg. Set to 1000ms if update every second
}


class Environment
{
public:
	
	//************************************
	// Method:    Environment
	// FullName:  Environment::Environment
	// Access:    public 
	// Returns:   
	// Qualifier:
	// Parameter: vector<int> _n 
	// The number of species in the environment
	// And _n.size() is the type of species
	//************************************
	explicit Environment(AVLTree<Species, int> _n);

	//************************************
	// Method:    GetEnvironment
	// FullName:  Environment::GetEnvironment
	// Access:    public 
	// Returns:   shared_ptr<Environment> A pointer to all animals
	// Qualifier:
	//************************************
	shared_ptr<vector<shared_ptr<Animal>>> GetEnvironment() const;

	//************************************
	// Method:    AddSpecies
	// FullName:  Environment::AddSpecies
	// Access:    public 
	// Returns:   The add is successful or not.
	// Qualifier:
	// Parameter: shared_ptr<Animal> new_animal
	//************************************
	bool AddSpecies(shared_ptr<Animal> new_animal);

	vector<int> GetDeadAnimals();

	//************************************
	// Method:    Update
	// FullName:  Environment::Update
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Update all animals in this environment.
	// And storing the positions of animals in the previous itertaions. 
	// You can use GetPrevPositions to get it.
	//************************************
	void Update();
	
	//************************************
	// Method:    GetClosetPair
	// FullName:  Environment::GetClosetPair
	// Access:    public 
	// Returns:   shared_ptr<Animal> Closest animal with corresponding species in the environment
	// Qualifier:
	// Parameter: const Animal & animal
	// Parameter: Species species Which species in the compare range. NULL_SPECIES if all species.
	//************************************
	static shared_ptr<Animal> GetClosetPair(const shared_ptr<vector<shared_ptr<Animal>>>& animals, const Animal& animal, Species species);
	static shared_ptr<Animal> GetClosetPair(const shared_ptr<vector<shared_ptr<Animal>>>& animals, const Animal& animal, std::set<Species> species);
private:
	
	// Storing animals
	shared_ptr<vector<shared_ptr<Animal>>> animals;

	// id of animals in the previous second
	std::set<int>prev_animals;

};

