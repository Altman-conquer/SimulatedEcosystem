#pragma once
#include "Animal.h"
#include"deer.h"
#include"cow.h"
class Wolf :
	public Animal
{
public:
	Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment);
	Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Gender _gender);

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

