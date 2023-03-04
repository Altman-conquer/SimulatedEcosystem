#pragma once
#include <utility>
#include <memory>
#include <map>
#include "Vector2D.h"
#include "Environment.h"
#include "Log.h"

class Environment;

using std::shared_ptr;
using std::vector;
using std::map;

enum class Species {
	Tiger,
	NULLSPECIES, // Use to denote a null species, useful in for loop (for int i=0; i<Species::NULLSPECIES; i++)
};

enum class Gene {
	TestName,
};

class Animal
{
public:
	
	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment);

	virtual Species GetSpecies() = 0;
	
	virtual void Update() = 0;

	Vector2D GetPosition();

protected:
	
	//************************************
	// Method:    Mutate
	// FullName:  Animal::Mutate
	// Access:    protected 
	// Returns:   void
	// Qualifier:
	// Change the gene value of this animal
	//************************************
	virtual void Mutate() = 0;
	
	
	//************************************
	// Method:    Breed
	// FullName:  Animal::Breed
	// Access:    virtual protected 
	// Returns:   void
	// Qualifier:
	// Born new animal with the same species in some probability
	//************************************
	virtual void Breed() = 0;
	
	Vector2D position;

	Vector2D velocity;
	
	bool isMale;

	shared_ptr<vector<shared_ptr<Animal>>> environment;

	map<Gene, float> genes;
};

