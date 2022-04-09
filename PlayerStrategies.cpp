#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include "GameEngine.h"

PlayerStrategy::PlayerStrategy()
{
	p = nullptr; //Player not set yet. Will set with setPlayer();
}

PlayerStrategy::~PlayerStrategy()
{
	p = nullptr; //Do NOT delete p! p is an actual Player so do not delete it!
}

void PlayerStrategy::setPlayer(Player* newPlayer)
{
	p = newPlayer;
}

Player* PlayerStrategy::getPlayer()
{
	return p;
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


NeutralPlayerStrategy::NeutralPlayerStrategy() : PlayerStrategy()
{
}

void NeutralPlayerStrategy::issueOrder(Order* pOrder)
{
}

vector<Territory*> NeutralPlayerStrategy::toAttack(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

vector<Territory*> NeutralPlayerStrategy::toDefend(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& other) : PlayerStrategy(other)
{
	this->p = other.p;
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


AggressivePlayerStrategy::AggressivePlayerStrategy() : PlayerStrategy()
{
}

AggressivePlayerStrategy::~AggressivePlayerStrategy()
{
	//Nothing to destroy
}

void AggressivePlayerStrategy::issueOrder(Order* pOrder)
{
}

vector<Territory*> AggressivePlayerStrategy::toAttack(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

vector<Territory*> AggressivePlayerStrategy::toDefend(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

AggressivePlayerStrategy::AggressivePlayerStrategy(const AggressivePlayerStrategy& other) : PlayerStrategy(other)
{
	this->p = other.p;
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

BenevolentPlayerStrategy::BenevolentPlayerStrategy(): BenevolentPlayerStrategy(nullptr)
{
}

void BenevolentPlayerStrategy::issueOrder(Order* pOrder)
{
	findWeakest();
	while (true)
	{
		break;		//deploy all armies to weakest, update weakest using findWeakest()
	}				//Advance onto weakest territories
}

vector<Territory*> BenevolentPlayerStrategy::toAttack(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

vector<Territory*> BenevolentPlayerStrategy::toDefend(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(Player* p) : PlayerStrategy(p)
{
	_weakest = nullptr;
	setWeakest();
}

BenevolentPlayerStrategy::BenevolentPlayerStrategy(const BenevolentPlayerStrategy& other) : PlayerStrategy(other)
{
	this->p = other.p;
	this->_weakest = other._weakest;
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
}


//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------
//-----------------------------------Cheater Player Stategy-------------------------------
//----------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------

CheaterPlayerStrategy::CheaterPlayerStrategy(): PlayerStrategy()
{
}

CheaterPlayerStrategy::~CheaterPlayerStrategy()
{
	//Nothing to delete here
}

void CheaterPlayerStrategy::issueOrder(Order* pOrder)
{	//toAttack returns a list of all neighbouring territories in main. replace get_territories() with toAttack
	for (auto ter : p->get_territories()) {
		ter->claim(p, true);
	}
	//automatically switches ownership of neigbouring countries to their own
}

vector<Territory*> CheaterPlayerStrategy::toAttack(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

vector<Territory*> CheaterPlayerStrategy::toDefend(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

CheaterPlayerStrategy::CheaterPlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

CheaterPlayerStrategy::CheaterPlayerStrategy(const CheaterPlayerStrategy& other) : PlayerStrategy(other)
{
	this->p = other.p;
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

HumanPlayerStrategy::HumanPlayerStrategy() : PlayerStrategy()
{
}

HumanPlayerStrategy::~HumanPlayerStrategy()
{
	//Nothing to delete here!
}

void HumanPlayerStrategy::issueOrder(Order* pOrder)
{
}

vector<Territory*> HumanPlayerStrategy::toAttack(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

vector<Territory*> HumanPlayerStrategy::toDefend(Territory* t)
{
	//TEMPORARY
	return vector<Territory*>();
}

HumanPlayerStrategy::HumanPlayerStrategy(Player* p) : PlayerStrategy(p)
{
}

HumanPlayerStrategy::HumanPlayerStrategy(const HumanPlayerStrategy& other) : PlayerStrategy(other)
{
	this->p = other.p;
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
