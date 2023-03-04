#pragma once
#include "Animal.h"
class Tiger :public Animal
{
public:
	Tiger(std::shared_ptr<vector<shared_ptr<Animal>>> _environment);

	Species GetSpecies() override;

	void Update() override;

};

