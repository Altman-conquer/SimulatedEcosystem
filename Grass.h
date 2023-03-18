#pragma once
#include "Animal.h"

class Grass :
    public Animal
{
public:
	Grass(shared_ptr<vector<shared_ptr<Animal>>> _environment);

	Grass(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position);

	Species GetSpecies() override;
	
	void Update() override;

	Age GetAge() override;

protected:
	void Mutate() override;
	
	void Breed() override;

	void Move() override;

	bool Eat(Animal& other) override;

	QString GetPicturePath() override;
private:

	float radius;
};

