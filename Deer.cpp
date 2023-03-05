#include "Deer.h"
#include "Utility.h"

Deer::Deer(shared_ptr<vector<shared_ptr<Animal>>> _environment) :Animal(_environment)
{
	position = RandomPositionVector();
	energy = AnimalConstants::COW_INITIAL_ENERGY;
}

Deer::Deer(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position, Gender _gender) :Animal(_environment)
{
	position = _position;
	energy = AnimalConstants::COW_INITIAL_ENERGY;
}


Species Deer::GetSpecies()
{
	return Species::Deer;
}

void Deer::Move()
{
	MoveState state = MoveState::Walk;
	Vector2D unit_direction;

	shared_ptr<Animal> nearest = Environment::GetClosetPair(environment, *this, { Species::Grass, Species::Wolf, Species::Tiger });
	
	if (Vector2D::GetDistance(nearest->GetPosition(), this->GetPosition()) <= AnimalConstants::PROBE_RADIUS)
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

		if (this->stamina >= AnimalConstants::DEER_MAX_STAMINA / 2)
		{
			velocity_scalar = AnimalConstants::DEER_MAX_VELOCITY;
		}
		else if (this->stamina > AnimalConstants::DEER_MIN_STAMINA)
		{
			velocity_scalar = AnimalConstants::DEER_MAX_VELOCITY * (this->stamina * 2 / AnimalConstants::DEER_MAX_STAMINA);
		}
		else
		{
			velocity_scalar = AnimalConstants::DEER_MIN_VELOCITY;
		}
	}
	else
	{
		if (RandomFloat(0.0, 1.0) <= AnimalConstants::DEER_IDLE_PROBABILITY)
		{
			velocity_scalar = 0;
			state = MoveState::Idle;
		}
		else
		{
			unit_direction = RandomUnitVector();
			velocity_scalar = AnimalConstants::DEER_MIN_VELOCITY;
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
		this->stamina = std::min(this->stamina + AnimalConstants::DEER_RECOVER_STAMINA_RATIO, AnimalConstants::DEER_MAX_STAMINA);
		this->energy = std::max(this->energy - AnimalConstants::DEER_CONSUME_ENERGY_RATIO, 0.0f);
	}
	else if (state == MoveState::Run)
	{
		this->stamina = std::max(this->stamina - AnimalConstants::DEER_CONSUME_STAMINA_RATIO, AnimalConstants::DEER_MIN_STAMINA);
	}
}

void Deer::Update()
{
	this->age_int += 1;
	if (age_int > AnimalConstants::DEER_MAX_AGE || energy <= 0.0)
		Die();
	Move();
	Breed();
}

Age Deer::GetAge()
{
	return Age(age_int >= AnimalConstants::DEER_ADULT_AGE);
}


void Deer::Mutate()
{
	return;
}

void Deer::Breed()
{
	if (GetAge() == Age::Child || RandomFloat(0.0, 1.0) > AnimalConstants::COW_BREED_PROBABILITY)
		return;

	shared_ptr<Animal> other = Environment::GetClosetPair(environment, *this, Species::Cow);
	if (other->GetGender() != gender)
	{
		bool is_success = false;
		if (other->GetGender() == Gender::Female && other->GetEnergy() > AnimalConstants::DEER_INITIAL_ENERGY * 2.0)
		{
			other->DecreaseEnergy(AnimalConstants::DEER_INITIAL_ENERGY);
			is_success = true;
		}
		else if (energy > AnimalConstants::DEER_INITIAL_ENERGY * 2.0)
		{
			DecreaseEnergy(AnimalConstants::DEER_INITIAL_ENERGY);
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
	if (other.GetSpecies() != Species::Grass)
		return false;
	if ((other.GetPosition() - position).GetLength() <= GetCollisionRadius())
	{
		energy = std::max(AnimalConstants::DEER_MAX_ENERGY, energy + other.GetEnergy());
		other.Die();
		return true;
	}
	return false;
}

