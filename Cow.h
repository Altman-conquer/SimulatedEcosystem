#pragma once
#include "Animal.h"
class Cow :
    public Animal
{
public:
	Cow(shared_ptr<vector<shared_ptr<Animal>>> _environment);

	Cow(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Gender _gender);

	Species GetSpecies() override;
	
	void Update() override;
	
	Age GetAge() override;

protected:
	void Mutate() override;


	void Breed() override;


	void Move() override;


	bool Eat(Animal& other) override;

};

