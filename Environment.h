#pragma once
#include <map>
#include <memory>
#include <vector>
#include "Vector2D.h"
#include "Animal.h"

class Animal;
enum class Species;

using std::map;
using std::vector;
using std::shared_ptr;


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
	explicit Environment(map<Species,int> _n);

	//************************************
	// Method:    GetEnvironment
	// FullName:  Environment::GetEnvironment
	// Access:    public 
	// Returns:   shared_ptr<Environment> A pointer to all animals
	// Qualifier:
	//************************************
	shared_ptr<vector<shared_ptr<Animal>>> GetEnvironment() const;

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
	// Method:    GetPrevPositions
	// FullName:  Environment::GetPrevPositions
	// Access:    public 
	// Returns:   shared_ptr<vector<Vector2D>>
	// Qualifier:
	// Get positions of animals in the t-1 iterations
	//************************************
	const shared_ptr<vector<Vector2D>> GetPrevPositions() const;
private:
	
	// Storing animals
	shared_ptr<vector<shared_ptr<Animal>>> animals;

	// Positions of animals in the previous iteration
	shared_ptr<vector<Vector2D>> prev_positions;
};

