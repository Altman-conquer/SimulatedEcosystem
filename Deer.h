#pragma once
#include "Animal.h"
class Deer:
	public Animal
{
public:
	Deer (std::shared_ptr<vector<shared_ptr<Animal>>> _environment);

	Species GetSpecies() {

	}

	void Update() override;

private:

};

