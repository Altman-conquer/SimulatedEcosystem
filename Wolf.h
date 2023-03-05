#pragma once
#include "Animal.h"
class Wolf :
	public Animal
{
	Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
		Vector2D _velocity, Gender _gender, map<Gene, float> _genes, float _stamina, float _energy);

	Species GetSpecies() override;

	void Update() override;



protected:
	void Mutate() override;

	void Breed() override;

	bool Eat(Animal& other) override;

	void Move() override;
	
	Age GetAge() override;

private:
	

};

