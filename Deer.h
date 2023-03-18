#pragma once
#include "Utility.h"
#include "Animal.h"

class Deer:
	public Animal
{
public:

	Deer(shared_ptr<vector<shared_ptr<Animal>>> _environment);

	Deer(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Gender _gender);

	Species GetSpecies() override;

	void Update() override;

	QString GetPicturePath() override;

protected:
	void Move() override;

	void Mutate() override;

	Age GetAge() override; 

	void Breed() override;

	bool Eat(Animal& other) override;

private:

};

