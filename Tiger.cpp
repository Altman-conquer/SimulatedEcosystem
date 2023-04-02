#include "Tiger.h"
#include <memory>

Tiger::Tiger(std::shared_ptr<vector<shared_ptr<Animal>>> _environment) : Animal(_environment)
{
	position = RandomPositionVector();
	energy = AnimalConstants::INITIAL_ENERGY[int(Species::Tiger)];
	if_run_away = false;
}

Tiger::Tiger(shared_ptr<vector<shared_ptr<Animal>>> _environment, Vector2D _position) :Animal(_environment)
{
	position = _position;
	energy = AnimalConstants::INITIAL_ENERGY[int(Species::Tiger)];
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
	if (age_int > AnimalConstants::MAX_AGE[int(Species::Tiger)] || energy <= 0.0)
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
	return Age(this->age_int >= AnimalConstants::ADULT_AGE[int(Species::Tiger)]);
}

void Tiger::Mutate()
{
	throw std::logic_error("The method or operation is not implemented.");
}

void Tiger::Breed()
{
	if (isDead) return;
	if (RandomFloat(0.0, 1.0) > AnimalConstants::BREED_PROBABILITY[int(Species::Tiger)])
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
		if (female->GetEnergy() > AnimalConstants::INITIAL_ENERGY[int(Species::Tiger)] * 2)
		{//female check
			female->DecreaseEnergy(AnimalConstants::INITIAL_ENERGY[int(Species::Tiger)]);
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

		if (this->stamina >= AnimalConstants::MAX_STAMINA[int(Species::Tiger)] / 2)
		{
			velocity_scalar = AnimalConstants::MAX_VELOCITY[int(Species::Tiger)];
		}
		else if (this->stamina > AnimalConstants::MIN_STAMINA[int(Species::Tiger)])
		{
			velocity_scalar = AnimalConstants::MAX_VELOCITY[int(Species::Tiger)] * (this->stamina * 2 / AnimalConstants::MAX_STAMINA[int(Species::Tiger)]);
		}
		else
		{
			velocity_scalar = AnimalConstants::MIN_VELOCITY[int(Species::Tiger)];
		}
	}
	else
	{
		if (RandomFloat(0.0, 1.0) <= AnimalConstants::IDLE_PROBABILITY[int(Species::Tiger)])
		{
			velocity_scalar = 0;
			state = MoveState::Idle;
		}
		else
		{
			unit_direction = RandomUnitVector();
			velocity_scalar = AnimalConstants::MIN_VELOCITY[int(Species::Tiger)];
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
		this->stamina = std::min(this->stamina + AnimalConstants::RECOVER_STAMINA_RATIO[int(Species::Tiger)], AnimalConstants::MAX_STAMINA[int(Species::Tiger)]);
		this->energy = std::max(this->energy - AnimalConstants::CONSUME_ENERGY_RATIO[int(Species::Tiger)] , 0.0f);
	}
	else if (state == MoveState::Run)
	{
		this->stamina = std::max(this->stamina - AnimalConstants::CONSUME_STAMINA_RATIO[int(Species::Tiger)], AnimalConstants::MIN_STAMINA[int(Species::Tiger)]);
	}
}

bool Tiger::Eat(Animal& other)
{
	if (isDead) return false;
	if ((other.GetPosition() - position).GetLength() <= GetCollisionRadius())
	{
		energy += other.GetEnergy();
		energy = std::min(AnimalConstants::MAX_ENERGY[int(Species::Tiger)], energy);
		other.Die();
		return true;
	}
	return false;
}

QString Tiger::GetPicturePath() {
	return ":/sourcePicture/tiger (2).png";
}