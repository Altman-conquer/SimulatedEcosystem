#pragma once
#include "Animal.h"

class Deer:
	public Animal
{
public:
	Deer(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Vector2D velocity,
		bool _isMale, map<Gene, float> _genes, float _stamina, float _energy);

	Species GetSpecies() override;

	void Update() override;

protected:
	void Move() override;

	void Mutate() override;

	void Breed() override;

	bool Eat(Animal& other) override;

private:

};

