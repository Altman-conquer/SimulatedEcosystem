#include "Wolf.h"


Wolf::Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment) :Animal(_environment)
{
	position = RandomPositionVector(EnvironmentConstants::LOWER_BOUND, EnvironmentConstants::UPPER_BOUND);
	energy = AnimalConstants::INITIAL_ENERGY[int(Species::Wolf)];
}

Wolf::Wolf(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Gender _gender) :Animal(_environment)
{
	position = _position;
	energy = AnimalConstants::INITIAL_ENERGY[int(Species::Wolf)];

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
	if (isDead) return;
	if (GetAge() == Age::Child || RandomFloat(0.0, 1.0) > AnimalConstants::BREED_PROBABILITY[int(Species::Wolf)])
		return;

	shared_ptr<Animal> other = Environment::GetClosetPair(environment, *this, Species::Wolf);
	if (other && other->GetGender() != gender)
	{
		bool is_success = false;
		if (other->GetGender() == Gender::Female && other->GetEnergy() > AnimalConstants::INITIAL_ENERGY[int(Species::Wolf)])
		{
			other->DecreaseEnergy(AnimalConstants::INITIAL_ENERGY[int(Species::Wolf)]);
			is_success = true;
		}
		else if (energy > AnimalConstants::INITIAL_ENERGY[int(Species::Wolf)])
		{
			DecreaseEnergy(AnimalConstants::INITIAL_ENERGY[int(Species::Wolf)]);
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
	if (isDead) return false;
	if ((other.GetPosition() - position).GetLength() <= GetCollisionRadius())
	{
		if (other.GetSpecies() == Species::Cow || other.GetSpecies() == Species::Deer)
		{
			energy += AnimalConstants::ENERGY_TRANSFORMATION_RATIO[int(Species::Wolf)] * other.GetEnergy();
			other.Die(); 
			return true;
		}
		else 
			return false;
	}
	else 
		return false;
}


void Wolf::Move()
{
	if (isDead) return;
	//calculate the magnitude of velocity

	MoveState state;
	Vector2D unit_direction;

	shared_ptr<Animal> nearest = Environment::GetClosetPair(environment, *this, { Species::Cow, Species::Deer });
	if (nearest && Vector2D::GetDistance(nearest->GetPosition(), this->GetPosition()) <= AnimalConstants::PROBE_RADIUS)
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
		if (this->stamina >= AnimalConstants::MAX_STAMINA[int(Species::Wolf)] / 2)
		{
			speed = AnimalConstants::MAX_VELOCITY[int(Species::Wolf)];
		}
		else if (this->stamina > AnimalConstants::MAX_STAMINA[int(Species::Wolf)])
		{
			speed = AnimalConstants::MAX_VELOCITY[int(Species::Wolf)] * (this->stamina * 2 / AnimalConstants::MAX_STAMINA[int(Species::Wolf)]);
		}
		else
		{
			speed = AnimalConstants::MIN_VELOCITY[int(Species::Wolf)];
		}
	}
	else
	{
		if (RandomFloat(0.0, 1.0) <= AnimalConstants::IDLE_PROBABILITY[int(Species::Wolf)])
		{
			speed = 0;
			unit_direction = Vector2D(0, 0);
			state = MoveState::Idle;
		}
		else
		{
			unit_direction = RandomUnitVector();
			speed = AnimalConstants::MIN_VELOCITY[int(Species::Wolf)];
			state = MoveState::Walk;
		}
	}


	//Get Direction
	this->velocity = unit_direction * speed;

	//update position
	this->position = this->position + this->velocity;

	if (state == MoveState::Idle || state == MoveState::Walk)
	{
		this->stamina = std::min(this->stamina + AnimalConstants::RECOVER_STAMINA_RATIO[int(Species::Wolf)], AnimalConstants::MAX_STAMINA[int(Species::Wolf)]);
		this->energy = std::max(this->energy - AnimalConstants::CONSUME_ENERGY_RATIO[int(Species::Wolf)] , 0.0f);
	}
	else if (state == MoveState::Run)
	{
		this->stamina = std::max(this->stamina - AnimalConstants::CONSUME_STAMINA_RATIO[int(Species::Wolf)], AnimalConstants::MIN_STAMINA[int(Species::Wolf)]);
	}

}

void Wolf::Update()
{
	if (isDead) return;
	age_int += 1;
	prev_position = position;
	if (age_int > AnimalConstants::MAX_AGE[int(Species::Wolf)] || energy <= 0.0)
		Die();
	Move();
	Breed();
}

Age Wolf::GetAge()
{
	return Age(this->age_int >= AnimalConstants::ADULT_AGE[int(Species::Wolf)]);
}

QString Wolf::GetPicturePath()
{
	return ":/sourcePicture/wolf.png";
}