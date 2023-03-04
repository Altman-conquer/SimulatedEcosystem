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

enum class State {
	Walk,
	Run,
	Idle,
};

enum class Gene {
	TestName,
};



class Animal
{
public:

	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment);
		
	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Vector2D velocity, bool _isMale, map<Gene, float> _genes);

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

	Vector2D GetPosition();

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
	int age;

	int stamina;
	
	int energy;

	// Used to identify an animal
	const int id;

private:
	
	static int animalCount;
};

