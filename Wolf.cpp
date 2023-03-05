#include "Wolf.h"

Wolf::Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position,
	Vector2D _velocity, Gender _gender, map<Gene, float> _genes, float _stamina, float _energy) :Animal(_environment, _position,
		_velocity, _gender, _genes, _stamina, _energy)
{
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
	Log::LogMessage("The method or operation is not implemented.", LogLevel::Error);
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

	shared_ptr<Animal> nearest = Environment::GetClosetPair(this->environment, *this, { Species::Cow, Species::Deer });
	if (Vector2D::GetDistance(nearest->GetPosition(), this->GetPosition()) <= AnimalConstants::DEER_PROBE_RADIUS)
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