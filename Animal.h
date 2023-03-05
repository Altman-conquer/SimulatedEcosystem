#pragma once
#include <utility>
#include <memory>
#include <map>
#include "Environment.h"
#include "Log.h"
#include <QString>


class Environment;
class Vector2D;

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

enum class Gender {
	Male,
	Female,
};

enum class Gene {
	TestName,
};


namespace AnimalConstants {

	// Age limits of animals to tell it is adult or not.
	extern const int COW_ADULT_AGE;

	extern const int GRASS_ADULT_AGE;
	
	extern const int Deer_ADULT_AGE;
	
	extern const int WOLF_ADULT_AGE;

	// Max age of animals
	extern const int COW_MAX_AGE;

	extern const float GRASS_INITIAL_RADIUS;

	extern const float GRASS_GROWTH_SPEED; // radius += GRASS_GROWTH_SPEED;

	extern const int Deer_MAX_AGE;

	extern const int WOLF_MAX_AGE;

	// Breed probability of animals
	extern const float GRASS_BREED_PROBABILITY;

	extern const float DEER_BREED_PROBABILITY;

	// Breed radius of grass
	extern const float GRASS_BREED_RADIUS;

	//Max stamina of animals
	extern const float DEER_MAX_STAMINA;

	extern const float WOLF_MAX_STAMINA;

	//Min stamina of animals
	extern const float DEER_MIN_STAMINA;

	extern const float WOLF_MIN_STAMINA;

	//Max velocity of animals
	extern const float DEER_MAX_VELOCITY;

	extern const float WOLF_MAX_VELOCITY;

	//Min velocity of animals
	extern const float DEER_MIN_VELOCITY;

	extern const float WOLF_MIN_VELOCITY;

	//Energy transformation ratio
	extern const float DEER_ENERGY_TRANSFORMATION_RATIO;

	// the energy of grass will increase every tick
	extern const float GRASS_RECOVER_SPEED;

	

	extern const float WOLF_ENERGY_TRANSFORMATION_RATIO;
}

class Animal
{
public:

	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment);
		
	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
		Vector2D _velocity, Gender _gender, map<Gene, float> _genes, float _stamina, float _energy);

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

	int GetID();
	
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

	Gender GetGender();

	float GetEnergy();

	Vector2D GetPosition() const;

	//************************************
	// Method:    GetDirection
	// FullName:  Animal::GetDirection
	// Access:    public 
	// Returns:   A unit vector of the moving direction of this animal.
	// Qualifier: const
	//************************************
	Vector2D GetDirection() const;

	bool operator==(const Animal& other)const;


	//************************************
	// Method:    Die
	// FullName:  Animal::Die
	// Access:    public 
	// Returns:   bool
	// Qualifier:
	// Kill the animal if it is too old or is being ate.
	//************************************
	bool Die();
	
  
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
	
	Gender gender;

	shared_ptr<vector<shared_ptr<Animal>>> environment;

	map<Gene, float> genes;

	//Add 1 in every update
	int age_int;

	float stamina; 
	
	float energy;

	// Used to identify an animal
	const int id;


private:
	
	static int animalCount;
};

