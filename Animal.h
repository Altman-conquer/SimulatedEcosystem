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

enum class MoveState {
	Run,
	Walk,
	Idle,
};

namespace AnimalConstants {
	//Breed radius

	extern const float BREED_RADIUS;

	// The distance of crash
	extern const float CHILD_DISTANCE;

	extern const float ADULT_DISTANCE; 

	// Age limits of animals to tell it is adult or not.
	extern const int GRASS_ADULT_AGE;

	extern const int COW_ADULT_AGE;
	
	extern const int DEER_ADULT_AGE;
	
	extern const int WOLF_ADULT_AGE;

	extern const int TIGER_ADULT_AGE;
	
	// Max age of animals
	extern const int COW_MAX_AGE;

	extern const int DEER_MAX_AGE;

	extern const int WOLF_MAX_AGE;

	extern const int TIGER_MAX_AGE;

	// Breed probability of animals
	extern const float GRASS_BREED_PROBABILITY;

	extern const float TIGER_BREED_PROBABILITY;
	
	extern const float COW_BREED_PROBABILITY;

	extern const float DEER_BREED_PROBABILITY;

	extern const float WOLF_BREED_PROBABILITY;

	// Breed radius of grass
	extern const float BREED_RADIUS;

	// The stating energy
	extern const float TIGER_INITIAL_ENERGY;
	extern const float WOLF_INITIAL_ENERGY;
	extern const float DEER_INITIAL_ENERGY;
	extern const float COW_INITIAL_ENERGY; 
	extern const float GRASS_INITIAL_ENERGY;

	// Breed radius

	//Max stamina of animals
	extern const float COW_MAX_STAMINA;
	
	extern const float DEER_MAX_STAMINA;

	extern const float WOLF_MAX_STAMINA;

	extern const float TIGER_MAX_STAMINA;

	//Min stamina of animals
	extern const float COW_MIN_STAMINA;
	
	extern const float DEER_MIN_STAMINA;

	extern const float WOLF_MIN_STAMINA;

	extern const float TIGER_MIN_STAMINA;


	//Max velocity of animals
	extern const float COW_MAX_VELOCITY;
	
	extern const float DEER_MAX_VELOCITY;

	extern const float WOLF_MAX_VELOCITY;

	extern const float TIGER_MAX_VELOCITY;

	//Min velocity of animals
	extern const float COW_MIN_VELOCITY;

	extern const float DEER_MIN_VELOCITY;

	extern const float WOLF_MIN_VELOCITY;

	extern const float TIGER_MIN_VELOCITY;

	//Energy transformation ratio
	extern const float COW_ENERGY_TRANSFORMATION_RATIO;

	extern const float DEER_ENERGY_TRANSFORMATION_RATIO;

	extern const float WOLF_ENERGY_TRANSFORMATION_RATIO;
	

	extern const float TIGER_ENERGY_TRANSFORMATION_RATIO;
	
	// the energy of grass will increase every tick
	extern const float GRASS_RECOVER_SPEED;


	//Energy consume ratio
	extern const float COW_CONSUME_ENERGY_RATIO;

	extern const float DEER_CONSUME_ENERGY_RATIO;

	extern const float WOLF_CONSUME_ENERGY_RATIO;

	extern const float TIGER_CONSUME_ENERGY_RATIO;


	extern const float WOLF_CONSUME_ENERGY_RATIO;

	//recover stamina ratio
	extern const float COW_RECOVER_STAMINA_RATIO;

	extern const float DEER_RECOVER_STAMINA_RATIO;

	extern const float WOLF_RECOVER_STAMINA_RATIO;

	extern const float TIGER_RECOVER_STAMINA_RATIO;


	extern const float TIGER_RECOVER_STAMINA_RATIO;

	//consume stamina ratio
	extern const float COW_CONSUME_STAMINA_RATIO;

	extern const float DEER_CONSUME_STAMINA_RATIO;

	extern const float WOLF_CONSUME_STAMINA_RATIO;

	extern const float TIGER_CONSUME_STAMINA_RATIO;
	
	extern const float COW_CONSUME_STAMINA_RATIO;
	
	extern const float TIGER_CONSUME_STAMINA_RATIO;

	extern const float WOLF_CONSUME_STAMINA_RATIO;

	

	//probe radius of animals
	extern const float DEER_PROBE_RADIUS;

	extern const float COW_PROBE_RADIUS;

	extern const float WOLF_PROBE_RADIUS;

	//maximal energy

	extern const float WOLF_MAXIMA_ENERGY;
	
	//probe radius of animals
	extern const float PROBE_RADIUS;

	//Idle probability of animals
	extern const float DEER_IDLE_PROBABILITY;

	extern const float COW_IDLE_PROBABILITY;

	extern const float WOLF_IDLE_PROBABILITY;

	extern const float TIGER_IDLE_PROBABILITY;

	//Max energy of animals
	extern const float TIGER_IDLE_PROBABILITY;

	extern const float COW_MAX_ENERGY;

	extern const float DEER_MAX_ENERGY;

	extern const float WOLF_MAX_ENERGY;

	extern const float TIGER_MAX_ENERGY;

	//Initial energy;

	extern const float TIGER_MAX_ENERGY;
	
	// Size of picture of the adult and child animal
	//extern const int SIZE_OF_CHILD = 50;

	//extern const int SIZE_OF_ADULT = 100;

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

	virtual QString GetPicturePath() = 0;

	float GetEnergy();

	bool DecreaseEnergy(float value);

	Vector2D GetPosition() const;

	//************************************
	// Method:    GetDirection
	// FullName:  Animal::GetDirection
	// Access:    public 
	// Returns:   A unit vector of the moving direction of this animal.
	// Qualifier: const
	//************************************
	Vector2D GetDirection() const;

	float GetCollisionRadius();

	bool operator==(const Animal& other)const;
	
	bool operator!=(const Animal& other)const;

	Vector2D GetPrevPosition() const;
	
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

	Vector2D prev_position;
	
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

