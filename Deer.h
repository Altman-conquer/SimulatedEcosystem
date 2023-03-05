#pragma once
#include "Animal.h"

class Deer:
	public Animal
{
public:
	Species GetSpecies() override;

	void Update() override;

protected:
	void Move() override;

	void Mutate() override;

	void Breed() override;

	bool Eat(Animal& other) override;

private:

};

