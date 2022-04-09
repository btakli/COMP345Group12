#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include "GameEngine.h"

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

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-----------------------------------Neutral Player Stategy-------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


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

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-----------------------------------Aggressive Player Stategy-------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------


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

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-----------------------------------Benevolent Player Stategy-------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

void BenevolentPlayerStrategy::issueOrder(Order* pOrder)
{
	findWeakest();
	while (true)
	{
				
	}
}

void BenevolentPlayerStrategy::toAttack(Territory* t)
{
}

void BenevolentPlayerStrategy::toDefend(Territory* t)
{

}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p)
{
	setWeakest();
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& other) : PlayerStrategy(other)
{

}

BenevolentPlayerStrategy& BenevolentPlayerStrategy::operator=(const BenevolentPlayerStrategy& rhs)
{
	this->p = rhs.p;
	this->_weakest = rhs._weakest;
	return *this;
}

BenevolentPlayerStrategy* BenevolentPlayerStrategy::clone()
{
	return new BenevolentPlayerStrategy(*this);
}

Territory* BenevolentPlayerStrategy::getWeakest()
{
	return _weakest;
}

void BenevolentPlayerStrategy::setWeakest()
{
	_weakest = new Territory;
	this->_weakest = p->get_territories()[0];
	int lowest = p->get_territories()[0]->get_stationed_army();
	for (auto ter : p->get_territories()) {
		if (ter->get_stationed_army() < _weakest->get_stationed_army()) {
			_weakest = ter;
		}
	}
}

void BenevolentPlayerStrategy::findWeakest()
{
	this->_weakest = p->get_territories()[0];
	int lowest = p->get_territories()[0]->get_stationed_army();
	for (auto ter : p->get_territories()) {
		if (ter->get_stationed_army() < _weakest->get_stationed_army()) {
			_weakest = ter;
		}
	}
}

BenevolentPlayerStrategy::~BenevolentPlayerStrategy() {
	delete _weakest;
	delete p;
}


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-----------------------------------Cheater Player Stategy-------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

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

//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-----------------------------------Human Player Stategy-------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

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
