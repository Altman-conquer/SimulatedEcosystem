#pragma once
#include "Animal.h"
class Wolf :
	public Animal
{
	Wolf(std::shared_ptr<vector<shared_ptr<Animal>>> _environment);

	Species GetSpecies() override;

	void Update() override;

protected:
	void Mutate() override;

	void Breed() override;
};

