#pragma once
#include <utility>
#include <memory>
#include "Environment.h"
#include "Log.h"
#include <QString>


class Environment;
class Vector2D;

using std::shared_ptr;
using std::vector;

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

	//probe radius of animals
	extern const float PROBE_RADIUS;

	// Age limits of animals to tell it is adult or not.
	extern const int ADULT_AGE[int(Species::NULLSPECIES)];
	
	// Max age of animals
	extern const int MAX_AGE[int(Species::NULLSPECIES)];

	// Breed probability of animals
	extern const float BREED_PROBABILITY[int(Species::NULLSPECIES)];

	// Breed radius of grass
	extern const float BREED_RADIUS;

	//Max stamina of animals
	extern const float MAX_STAMINA[int(Species::NULLSPECIES)];

	//Min stamina of animals
	extern const float MIN_STAMINA[int(Species::NULLSPECIES)];
	
	//Max velocity of animals
	extern const float MAX_VELOCITY[int(Species::NULLSPECIES)];

	//Min velocity of animals
	extern const float MIN_VELOCITY[int(Species::NULLSPECIES)];
	
	//Energy transformation ratio
	extern const float ENERGY_TRANSFORMATION_RATIO[int(Species::NULLSPECIES)];
	
	// the energy of grass will increase every tick
	extern const float GRASS_RECOVER_SPEED;


	//Energy consume ratio
	extern const float CONSUME_ENERGY_RATIO[int(Species::NULLSPECIES)];

	//recover stamina ratio
	extern const float RECOVER_STAMINA_RATIO[int(Species::NULLSPECIES)];

	//consume stamina ratio
	extern const float CONSUME_STAMINA_RATIO[int(Species::NULLSPECIES)];

	//Idle probability of animals
	extern const float IDLE_PROBABILITY[int(Species::NULLSPECIES)];

	// The stating energy
	extern const float INITIAL_ENERGY[int(Species::NULLSPECIES)];

	//maximal energy
	extern const float MAX_ENERGY[int(Species::NULLSPECIES)];

	//minimal energy
	extern const float MIN_ENERGY[int(Species::NULLSPECIES)];

	extern const float INITIAL_HEALTH[int(Species::NULLSPECIES)];

	extern const float DAMAGE[int(Species::NULLSPECIES)];
	
}

class Animal
{
public:

	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment);
		
	Animal(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
		Vector2D _velocity, Gender _gender, AVLTree<Gene, float> _genes, float _stamina, float _energy);

	virtual ~Animal();

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
	// Method:    GetSpecies
	// FullName:  Animal::GetSpecies
	// Access:    virtual public 
	// Returns:   Species
	// Qualifier:
	// Get what kind of animal it is.
	//************************************
	virtual Species GetSpecies() = 0;

	// Get unique ID of this animal
	int GetID();

	// Get age of this animal, return Age::Adult if it is adult. And it can breed new animal when it is adult. 
	virtual Age GetAge() = 0;

	// Get whether Male or Female this animal is.
	Gender GetGender();

	// Get the displaying picture path of this animal
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


	
  

	//************************************
	// Method:    Hurt
	// FullName:  Animal::Hurt
	// Access:    public 
	// Returns:   bool - Whether the health is greater than 0.  If false, should kill this anmial
	// Qualifier:
	// Parameter: float damage
	//************************************
	bool Hurt(float damage);
  
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

	// Used to store all animals
	shared_ptr<vector<shared_ptr<Animal>>> environment;

	AVLTree<Gene, float> genes;

	//Add 1 in every update
	int age_int;

	float stamina; 
	
	float energy;

	float health;

	// Used to identify an animal
	const int id;

	bool isDead;
private:
	
	static int animalCount;
};

