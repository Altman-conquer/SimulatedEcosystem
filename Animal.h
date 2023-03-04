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
	Grass,
	Cow,
	Deer,
	Wolf,
	Tiger,
	NULLSPECIES, // Use to denote a null species, useful in for loop (for int i=0; i<Species::NULLSPECIES; i++)
};


enum class Age {
	Child,
	Adult
};

enum class Gene {
	TestName,
};

namespace AnimalConstants {

	// Age limits of animals to tell it is adult or not.
	const int COW_ADULT_AGE = 50;
	
	const int GRASS_ADULT_AGE = 10;
	

	const int Deer_ADULT_AGE = 50;
	
	// Max age of animals
	const int COW_MAX_AGE = 100;

	const float GRASS_INITIAL_RADIUS = 1.0;
	
	const float GRASS_GROWTH_SPEED = 1.0; // radius += GRASS_GROWTH_SPEED;

	const int Deer_MAX_AGE = 100;

	// Breed probability of animals
	const float GRASS_BREED_PROBABILITY = 0.1;

	//Eat probability of animals
	const float Deer_EAT_PROBABILITY = 0.5;
}

class Animal
{
public:

	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment);
		
	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
		Vector2D velocity, bool _isMale, map<Gene, float> _genes, float _stamina, float _energy);

	virtual ~Animal();

	//************************************
	// Method:    GetSpecies
	// FullName:  Animal::GetSpecies
	// Access:    virtual public 
	// Returns:   Species
	// Qualifier:
	// Get what kind of animal it is.
	//************************************
	virtual Species GetSpecies() = 0;
	
	//************************************
	// Method:    Update
	// FullName:  Animal::Update
	// Access:    virtual public 
	// Returns:   void
	// Qualifier:
	// Update this animal.
	//************************************
	virtual void Update() = 0;

	//************************************
	// Method:    GetAge
	// FullName:  Animal::GetAge
	// Access:    virtual public 
	// Returns:   Age of this animal, if it is adult, it can call breed new animal.
	// Qualifier:
	//************************************
	virtual Age GetAge() = 0;

	Vector2D GetPosition() const;

	bool operator==(const Animal& other)const;
	
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

	
	//************************************
	// Method:    Move
	// FullName:  Animal::Move
	// Access:    virtual protected 
	// Returns:   void
	// Qualifier:
	//************************************
	virtual void Move() = 0;

	//************************************
	// Method:    Eat
	// FullName:  Animal::Eat
	// Access:    virtual protected 
	// Returns:   Whether the animal is ate successfully.
	// Qualifier:
	// Parameter: Animal & other
	//************************************
	virtual bool Eat(Animal& other) = 0;
	
	Vector2D position;

	Vector2D velocity;
	
	bool is_male;

	shared_ptr<vector<shared_ptr<Animal>>> environment;

	map<Gene, float> genes;

	//Add 1 in every update
	int age_int;

	int stamina;
	
	int energy;

	// Used to identify an animal
	const int id;

private:
	
	static int animalCount;
};

