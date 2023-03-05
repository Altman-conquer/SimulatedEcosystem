#pragma once
#include "Animal.h"
class Cow :
    public Animal
{
public:
	Species GetSpecies() override;
	

	void Update() override;


	Age GetAge() override;

protected:
	void Mutate() override;


	void Breed() override;


	void Move() override;


	bool Eat(Animal& other) override;

};

