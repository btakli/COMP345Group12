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

std::ostream& operator<<(std::ostream& out, const NeutralPlayerStrategy& neutral)
{
	out << "Neutral strategy: Computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player." << std::endl;
	out << "Player info:" << std::endl;
	out << *neutral.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const AggressivePlayerStrategy& aggressive)
{
	out << "Aggressive player: computer player that focuses on attack (deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore)." << std::endl;
	out << "Player info:" << std::endl;
	out << *aggressive.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const BenevolentPlayerStrategy& benevolent)
{
	out << "Benevolent player: computer player that focuses on protecting its weak countries (deploys or advances armies on its weakest countries, never advances to enemy territories)." << std::endl;
	out << "Player info:" << std::endl;
	out << *benevolent.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const CheaterPlayerStrategy& cheater)
{
	out << "Cheater player: computer player that automatically conquers all territories that are adjacent to its own territories(only once per turn)." << std::endl;
	out << "Player info:" << std::endl;
	out << *cheater.p;
	return out;
}

std::ostream& operator<<(std::ostream& out, const HumanPlayerStrategy& human)
{
	out << " Human player: requires user interactions to make decisions." << std::endl;
	out << "Player info:" << std::endl;
	out << *human.p;
	return out;
}

void NeutralPlayerStrategy::issueOrder(Order* pOrder)
{
}

void NeutralPlayerStrategy::toAttack(Territory* t)
{
}

void NeutralPlayerStrategy::toDefend(Territory* t)
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& other) : PlayerStrategy(other)
{
}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& rhs)
{
	this->p = rhs.p;
	return *this;
}

NeutralPlayerStrategy* NeutralPlayerStrategy::clone()
{
	return new NeutralPlayerStrategy(*this);
}

void AggressivePlayerStrategy::issueOrder(Order* pOrder)
{
}

void AggressivePlayerStrategy::toAttack(Territory* t)
{
}

void AggressivePlayerStrategy::toDefend(Territory* t)
{
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& other) : PlayerStrategy(other)
{
}

AggressivePlayerStrategy& AggressivePlayerStrategy::operator=(const AggressivePlayerStrategy& rhs)
{
	this->p = rhs.p;
	return *this;
}

AggressivePlayerStrategy* AggressivePlayerStrategy::clone()
{
	return new AggressivePlayerStrategy(*this);
}

void BenevolentPlayerStrategy::issueOrder(Order* pOrder)
{
}

void BenevolentPlayerStrategy::toAttack(Territory* t)
{
}

void BenevolentPlayerStrategy::toDefend(Territory* t)
{
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& other) : PlayerStrategy(other)
{
}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& rhs)
{
	this->p = rhs.p;
	return *this;
}

BenevolentPlayerStrategy* BenevolentPlayerStrategy::clone()
{
	return new BenevolentPlayerStrategy(*this);
}

void CheaterPlayerStrategy::issueOrder(Order* pOrder)
{
}

void CheaterPlayerStrategy::toAttack(Territory* t)
{
}

void CheaterPlayerStrategy::toDefend(Territory* t)
{
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& other) : PlayerStrategy(other)
{
}

CheaterPlayerStrategy& CheaterPlayerStrategy::operator=(const CheaterPlayerStrategy& rhs)
{
	this->p = rhs.p;
	return *this;
}

CheaterPlayerStrategy* CheaterPlayerStrategy::clone()
{
	return new CheaterPlayerStrategy(*this);
}

void HumanPlayerStrategy::issueOrder(Order* pOrder)
{
}

void HumanPlayerStrategy::toAttack(Territory* t)
{
}

void HumanPlayerStrategy::toDefend(Territory* t)
{
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& other) : PlayerStrategy(other)
{
}

HumanPlayerStrategy& HumanPlayerStrategy::operator=(const HumanPlayerStrategy& rhs)
{
	this->p = rhs.p;
	return *this;
}

HumanPlayerStrategy* HumanPlayerStrategy::clone()
{
	return new HumanPlayerStrategy(*this);
}
