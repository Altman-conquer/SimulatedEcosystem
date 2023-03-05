#include "Wolf.h"


Wolf::Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment) :Animal(_environment)
{
	position = RandomPositionVector();
	energy = AnimalConstants::COW_INITIAL_ENERGY;
}

Wolf::Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Gender _gender) :Animal(_environment)
{
	position = _position;
	energy = AnimalConstants::COW_INITIAL_ENERGY;

}
Species Wolf::GetSpecies()
{
	return Species::Wolf;
}

void Wolf::Mutate()
{
	Log::LogMessage("The method or operation is not implemented.", LogLevel::Error);
}

void Wolf::Breed()
{
	if (GetAge() == Age::Child || RandomFloat(0.0, 1.0) > AnimalConstants::WOLF_BREED_PROBABILITY)
		return;

	shared_ptr<Animal> other = Environment::GetClosetPair(environment, *this, Species::Wolf);
	if (other->GetGender() != gender)
	{
		bool is_success = false;
		if (other->GetGender() == Gender::Female && other->GetEnergy() > AnimalConstants::WOLF_INITIAL_ENERGY)
		{
			other->DecreaseEnergy(AnimalConstants::WOLF_INITIAL_ENERGY);
			is_success = true;
		}
		else if (energy > AnimalConstants::WOLF_INITIAL_ENERGY)
		{
			DecreaseEnergy(AnimalConstants::WOLF_INITIAL_ENERGY);
			is_success = true;
		}

		if (is_success)
		{
			shared_ptr<Animal> new_animal =
				std::make_shared<Wolf>(this->environment, RandomPositionVector(position, AnimalConstants::BREED_RADIUS), Gender(RandomInteger(0, 1)));
			this->environment->push_back(new_animal);
		}
	}
}

bool Wolf::Eat(Animal& other) 
{
	if ((other.GetPosition() - position).GetLength() <= GetCollisionRadius())
	{
		if (other.GetSpecies() == Species::Cow || other.GetSpecies() == Species::Deer)
		{
			energy += AnimalConstants::WOLF_ENERGY_TRANSFORMATION_RATIO * other.GetEnergy();
			return true;
			other.Die();
		}
		else return false;
	}
	else return false;
}


void Wolf::Move()
{	
	//calculate the magnitude of velocity

	MoveState state;
	Vector2D unit_direction;

	shared_ptr<Animal> nearest = Environment::GetClosetPair(environment, *this, { Species::Cow, Species::Deer });
	if (Vector2D::GetDistance(nearest->GetPosition(), this->GetPosition()) <= AnimalConstants::PROBE_RADIUS)
	{
		unit_direction = (nearest->GetPosition() - this->GetPosition()).GetNormalized();
		state = MoveState::Run;
	}
	else
	{
		state = MoveState::Walk;
	}

	float speed = 0;

	if (state == MoveState::Run) {
		if (this->stamina >= AnimalConstants::WOLF_MAX_STAMINA / 2)
		{
			speed = AnimalConstants::WOLF_MAX_VELOCITY;
		}
		else if (this->stamina > AnimalConstants::WOLF_MAX_STAMINA)
		{
			speed = AnimalConstants::WOLF_MAX_VELOCITY * (this->stamina * 2 / AnimalConstants::WOLF_MAX_STAMINA);
		}
		else
		{
			speed = AnimalConstants::WOLF_MIN_VELOCITY;
		}
	}

	else
	{
		if (RandomFloat(0.0, 1.0) <= AnimalConstants::WOLF_IDLE_PROBABILITY)
		{
			speed = 0;
			state = MoveState::Idle;
		}
		else
		{
			unit_direction = RandomUnitVector();
			speed = AnimalConstants::WOLF_MIN_VELOCITY;
			state = MoveState::Walk;
		}
	}


	//Get Direction
	this->velocity = unit_direction * speed;

	//update position
	this->position = this->position + this->velocity;

	if (state == MoveState::Idle || state == MoveState::Walk)
	{
		this->stamina = std::min(this->stamina + AnimalConstants::WOLF_RECOVER_STAMINA_RATIO, AnimalConstants::WOLF_MAX_STAMINA);
		this->energy = std::max(this->energy - AnimalConstants::WOLF_CONSUME_ENERGY_RATIO, 0.0f);
	}
	else if (state == MoveState::Run)
	{
		this->stamina = std::max(this->stamina - AnimalConstants::WOLF_CONSUME_STAMINA_RATIO, AnimalConstants::WOLF_MIN_STAMINA);
	}

}

void Wolf::Update()
{
	age_int++;
	Wolf::Move();
}

Age Wolf::GetAge()
{
	return Age(this->age_int >= AnimalConstants::WOLF_ADULT_AGE);
}