#pragma once
#include "Animal.h"
class Tiger :public Animal
{
public:
	Tiger(std::shared_ptr<vector<shared_ptr<Animal>>> _environment);

	Tiger(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position);

	Species GetSpecies() override;

	void Update() override;

	Age GetAge() override;

protected:
	void Mutate() override;


	void Breed() override;


	void Move() override;


	bool Eat(Animal& other) override;

private:
	shared_ptr<Animal> closest;
	bool if_run_away;

	QString GetPicturePath() override;
};

