#include "Deer.h"
#include "Utility.h"
#include <memory>


Deer::Deer(shared_ptr<vector<shared_ptr<Animal>>> _environment) :Animal(_environment)
{
	position = RandomPositionVector();
	energy = AnimalConstants::INITIAL_ENERGY[int(Species::Deer)];
}

Deer::Deer(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Gender _gender) :Animal(_environment)
{
	position = _position;
	energy = AnimalConstants::INITIAL_ENERGY[int(Species::Deer)];
}


Species Deer::GetSpecies()
{
	return Species::Deer;
}

void Deer::Move()
{
	if (isDead) return;
	MoveState state = MoveState::Walk;
	Vector2D unit_direction;

	shared_ptr<Animal> nearest = Environment::GetClosetPair(environment, *this, { Species::Grass, Species::Wolf, Species::Tiger });
	
	if (nearest && Vector2D::GetDistance(nearest->GetPosition(), this->GetPosition()) <= AnimalConstants::PROBE_RADIUS)
	{
		if (nearest->GetSpecies() == Species::Grass)
			unit_direction = (nearest->GetPosition() - this->GetPosition()).GetNormalized();
		else
			unit_direction = (this->GetPosition() - nearest->GetPosition()).GetNormalized();
		state = MoveState::Run;
	}

	float velocity_scalar;

	if (state == MoveState::Run)
	{

		if (this->stamina >= AnimalConstants::MAX_STAMINA[int(Species::Deer)] / 2)
		{
			velocity_scalar = AnimalConstants::MAX_VELOCITY[int(Species::Deer)];
		}
		else if (this->stamina > AnimalConstants::MIN_STAMINA[int(Species::Deer)])
		{
			velocity_scalar = AnimalConstants::MAX_VELOCITY[int(Species::Deer)] * (this->stamina * 2 / AnimalConstants::MAX_STAMINA[int(Species::Deer)]);
		}
		else
		{
			velocity_scalar = AnimalConstants::MIN_VELOCITY[int(Species::Deer)];
		}
	}
	else
	{
		if (RandomFloat(0.0, 1.0) <= AnimalConstants::IDLE_PROBABILITY[int(Species::Deer)])
		{
			velocity_scalar = 0.0f;
			unit_direction = Vector2D(0, 0);
			state = MoveState::Idle;
		}
		else
		{
			unit_direction = RandomUnitVector();
			velocity_scalar = AnimalConstants::MIN_VELOCITY[int(Species::Deer)];
			state = MoveState::Walk;
		}
	}

	//Get Direction
	this->velocity = unit_direction * velocity_scalar;

	//update position
	this->position = this->position + this->velocity;

	//update stamina and energy
	if (state == MoveState::Idle || state == MoveState::Walk)
	{
		this->stamina = std::min(this->stamina + AnimalConstants::RECOVER_STAMINA_RATIO[int(Species::Deer)], AnimalConstants::MAX_STAMINA[int(Species::Deer)]);
		this->energy = std::max(this->energy - AnimalConstants::CONSUME_ENERGY_RATIO[int(Species::Deer)] , 0.0f);
	}
	else if (state == MoveState::Run)
	{
		this->stamina = std::max(this->stamina - AnimalConstants::CONSUME_STAMINA_RATIO[int(Species::Deer)], AnimalConstants::MIN_STAMINA[int(Species::Deer)]);
	}
}

void Deer::Update()
{
	if (isDead) return;
	this->age_int += 1;
	prev_position = position;

	if (age_int > AnimalConstants::MAX_AGE[int(Species::Deer)] || energy <= 0.0)
		Die();

	Move();
	Breed();
}

Age Deer::GetAge()
{
	return Age(age_int >= AnimalConstants::ADULT_AGE[int(Species::Deer)]);
}


void Deer::Mutate()
{
	return;
}

void Deer::Breed()
{
	if (isDead) return;
	if (GetAge() == Age::Child || RandomFloat(0.0, 1.0) > AnimalConstants::BREED_PROBABILITY[int(Species::Deer)])
		return;

	shared_ptr<Animal> other = Environment::GetClosetPair(environment, *this, Species::Cow);
	if (other->GetGender() != gender)
	{
		bool is_success = false;
		if (other->GetGender() == Gender::Female && other->GetEnergy() > AnimalConstants::INITIAL_ENERGY[int(Species::Deer)] * 2.0)
		{
			other->DecreaseEnergy(AnimalConstants::INITIAL_ENERGY[int(Species::Deer)]);
			is_success = true;
		}
		else if (energy > AnimalConstants::INITIAL_ENERGY[int(Species::Deer)] * 2.0)
		{
			DecreaseEnergy(AnimalConstants::INITIAL_ENERGY[int(Species::Deer)]);
			is_success = true;
		}

		if (is_success)
		{
			shared_ptr<Animal> new_animal =
				std::make_shared<Deer>(this->environment, RandomPositionVector(position, AnimalConstants::BREED_RADIUS), Gender(RandomInteger(0, 1)));
			this->environment->push_back(new_animal);
		}
	}
}

bool Deer::Eat(Animal& other)
{
	if (isDead) return false;
	if (other.GetSpecies() != Species::Grass)
		return false;
	if ((other.GetPosition() - position).GetLength() <= GetCollisionRadius())
	{
		energy = std::max(AnimalConstants::MAX_ENERGY[int(Species::Deer)], energy + other.GetEnergy());
		other.Die();
		return true;
	}
	return false;
}

QString Deer::GetPicturePath()
{
	return ":/sourcePicture/deer.png";
}

