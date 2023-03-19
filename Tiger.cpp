#include "Tiger.h"
#include <memory>

Tiger::Tiger(std::shared_ptr<vector<shared_ptr<Animal>>> _environment) : Animal(_environment)
{
	position = RandomPositionVector();
	energy = AnimalConstants::TIGER_INITIAL_ENERGY;
	if_run_away = false;
}

Tiger::Tiger(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position) :Animal(_environment)
{
	position = _position;
	energy = AnimalConstants::TIGER_INITIAL_ENERGY;
	if_run_away = false;
}


Species Tiger::GetSpecies()
{
	return Species::Tiger;
}

void Tiger::Update()//behavior algorithm 
{
	if (isDead) return;
	//die
	if (age_int > AnimalConstants::TIGER_MAX_AGE || energy <= 0.0)
		Die();

	//grow up
	age_int += 1;
	Log::LogMessage("Tiger update", LogLevel::Info);

	//check surrounding
	closest = Environment::GetClosetPair(environment, *this, Species::NULLSPECIES);
	float dis = Vector2D::GetDistance(this->GetPosition(), closest->GetPosition());

	if (closest->GetSpecies() == Species::Tiger)//same species
	{//check run or breed
		if (this->GetAge() == Age::Adult&&//adult
			closest->GetGender() != this->GetGender()&&//different gender
			dis < AnimalConstants::ADULT_DISTANCE * 2)//close to
		{//breed
			Breed();
		}
		else
		{//run away
			if_run_away = true;
		}
	} 
	else 
	{//check eatable
		if (closest->GetSpecies() == Species::Cow || closest->GetSpecies() == Species::Deer)
			Eat(*closest);
	}

	Move();
}

Age Tiger::GetAge()
{
	return Age(this->age_int >= AnimalConstants::TIGER_ADULT_AGE);
}

void Tiger::Mutate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Tiger::Breed()
{
	if (isDead) return;
	if (RandomFloat(0.0, 1.0) > AnimalConstants::TIGER_BREED_PROBABILITY) 
		return;
	//breed probability
		shared_ptr<Tiger> female;
		if (this->gender == Gender::Male)
		{
			female = std::dynamic_pointer_cast<Tiger>(closest);
		}
		else
		{
			female = std::make_shared<Tiger>(*this);
		}
		if (female->GetEnergy() > AnimalConstants::TIGER_INITIAL_ENERGY * 2)
		{//female check
			female->DecreaseEnergy(AnimalConstants::TIGER_INITIAL_ENERGY);
			//give broth
			shared_ptr<Animal> new_animal = std::make_shared<Tiger>(this->environment,
				RandomPositionVector(position, AnimalConstants::BREED_RADIUS));
			this->environment->push_back(new_animal);
			Log::LogMessage("Tiger breed", LogLevel::Info);
		}
}

void Tiger::Move()
{
	if (isDead) return;
	//move direction
	Vector2D unit_direction;
	MoveState state = MoveState::Walk;

	shared_ptr<Animal> nearest = Environment::GetClosetPair(environment, *this, { Species::Cow, Species::Deer, Species::Tiger });

	if (Vector2D::GetDistance(nearest->GetPosition(), this->GetPosition()) <= AnimalConstants::PROBE_RADIUS)
	{//in the horizon
		if (nearest->GetSpecies() == Species::Cow|| nearest->GetSpecies() == Species::Deer)
			unit_direction = (nearest->GetPosition() - this->GetPosition()).GetNormalized();
		else
			unit_direction = (this->GetPosition() - nearest->GetPosition()).GetNormalized();
		state = MoveState::Run;
	}

	if (if_run_away)//meet same gender tiger
	{
		state = MoveState::Run;
		unit_direction = ((closest->GetPosition() - this->GetPosition()).GetNormalized())*(-1);
	}

	float velocity_scalar;

	if (state == MoveState::Run)
	{

		if (this->stamina >= AnimalConstants::TIGER_MAX_STAMINA / 2)
		{
			velocity_scalar = AnimalConstants::TIGER_MAX_VELOCITY;
		}
		else if (this->stamina > AnimalConstants::TIGER_MIN_STAMINA)
		{
			velocity_scalar = AnimalConstants::TIGER_MAX_VELOCITY * (this->stamina * 2 / AnimalConstants::TIGER_MAX_STAMINA);
		}
		else
		{
			velocity_scalar = AnimalConstants::TIGER_MIN_VELOCITY;
		}
	}
	else
	{
		if (RandomFloat(0.0, 1.0) <= AnimalConstants::TIGER_IDLE_PROBABILITY)
		{
			velocity_scalar = 0;
			state = MoveState::Idle;
		}
		else
		{
			unit_direction = RandomUnitVector();
			velocity_scalar = AnimalConstants::TIGER_MIN_VELOCITY;
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
		this->stamina = std::min(this->stamina + AnimalConstants::TIGER_RECOVER_STAMINA_RATIO, AnimalConstants::TIGER_MAX_STAMINA);
		this->energy = std::max(this->energy - AnimalConstants::TIGER_CONSUME_ENERGY_RATIO, 0.0f);
	}
	else if (state == MoveState::Run)
	{
		this->stamina = std::max(this->stamina - AnimalConstants::TIGER_CONSUME_STAMINA_RATIO, AnimalConstants::TIGER_MIN_STAMINA);
	}
}

bool Tiger::Eat(Animal& other)
{
	if (isDead) return;
	if ((other.GetPosition() - position).GetLength() <= GetCollisionRadius())
	{
		energy += other.GetEnergy();
		energy = std::min(AnimalConstants::TIGER_MAX_ENERGY, energy);
		other.Die();
		return true;
	}
	return false;
}

QString Tiger::GetPicturePath() {
	return ":/sourcePicture/tiger (2).png";
}