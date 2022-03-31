#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"

void PlayerStrategy::setPlayer(Player* newPlayer)
{
	p = newPlayer;
}

PlayerStrategy::PlayerStrategy(Player* p): p(p)
{
}

PlayerStrategy::PlayerStrategy(const PlayerStrategy& other): p(other.p)
{
}

PlayerStrategy& PlayerStrategy::operator=(const PlayerStrategy& rhs)
{
	this->p = rhs.p;
	return *this;
}

std::ostream& operator<<(std::ostream& out, const PlayerStrategy& playerStrategy)
{
	out << "PlayerStrategy class pointing to player with the following info:" << std::endl;
	out << *playerStrategy.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Neutral& neutral)
{
	out << "Neutral strategy: Computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player." << std::endl;
	out << "Player info:" << std::endl;
	out << *neutral.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Aggressive& aggressive)
{
	out << "Aggressive player: computer player that focuses on attack (deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore)." << std::endl;
	out << "Player info:" << std::endl;
	out << *aggressive.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Benevolent& benevolent)
{
	out << "Benevolent player: computer player that focuses on protecting its weak countries (deploys or advances armies on its weakest countries, never advances to enemy territories)." << std::endl;
	out << "Player info:" << std::endl;
	out << *benevolent.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Cheater& cheater)
{
	out << "Cheater player: computer player that automatically conquers all territories that are adjacent to its own territories(only once per turn)." << std::endl;
	out << "Player info:" << std::endl;
	out << *cheater.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const Human& human)
{
	out << " Human player: requires user interactions to make decisions." << std::endl;
	out << "Player info:" << std::endl;
	out << *human.p;
	return out;
}

void Neutral::issueOrder(Order* pOrder)
{
}

void Neutral::toAttack(Territory* t)
{
}

void Neutral::toDefend(Territory* t)
{
}

Neutral::Neutral(Player* p) : PlayerStrategy(p)
{
}

Neutral::Neutral(const Neutral& other) : PlayerStrategy(other)
{
}

Neutral& Neutral::operator=(const Neutral& rhs)
{
	this->p = rhs.p;
	return *this;
}

Neutral* Neutral::clone()
{
	return new Neutral(*this);
}

void Aggressive::issueOrder(Order* pOrder)
{
}

void Aggressive::toAttack(Territory* t)
{
}

void Aggressive::toDefend(Territory* t)
{
}

Aggressive::Aggressive(Player* p) : PlayerStrategy(p)
{
}

Aggressive::Aggressive(const Aggressive& other) : PlayerStrategy(other)
{
}

Aggressive& Aggressive::operator=(const Aggressive& rhs)
{
	this->p = rhs.p;
	return *this;
}

Aggressive* Aggressive::clone()
{
	return new Aggressive(*this);
}

void Benevolent::issueOrder(Order* pOrder)
{
}

void Benevolent::toAttack(Territory* t)
{
}

void Benevolent::toDefend(Territory* t)
{
}

Benevolent::Benevolent(Player* p) : PlayerStrategy(p)
{
}

Benevolent::Benevolent(const Benevolent& other) : PlayerStrategy(other)
{
}

Benevolent& Benevolent::operator=(const Benevolent& rhs)
{
	this->p = rhs.p;
	return *this;
}

Benevolent* Benevolent::clone()
{
	return new Benevolent(*this);
}

void Cheater::issueOrder(Order* pOrder)
{
}

void Cheater::toAttack(Territory* t)
{
}

void Cheater::toDefend(Territory* t)
{
}

Cheater::Cheater(Player* p) : PlayerStrategy(p)
{
}

Cheater::Cheater(const Cheater& other) : PlayerStrategy(other)
{
}

Cheater& Cheater::operator=(const Cheater& rhs)
{
	this->p = rhs.p;
	return *this;
}

Cheater* Cheater::clone()
{
	return new Cheater(*this);
}

void Human::issueOrder(Order* pOrder)
{
}

void Human::toAttack(Territory* t)
{
}

void Human::toDefend(Territory* t)
{
}

Human::Human(Player* p) : PlayerStrategy(p)
{
}

Human::Human(const Human& other) : PlayerStrategy(other)
{
}

Human& Human::operator=(const Human& rhs)
{
	this->p = rhs.p;
	return *this;
}

Human* Human::clone()
{
	return new Human(*this);
}
