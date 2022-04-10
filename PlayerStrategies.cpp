#include "PlayerStrategies.h"
#include "Player.h"
#include "Orders.h"
#include "GameEngine.h"
#include "Map.h"

PlayerStrategy::PlayerStrategy(): PlayerStrategy(nullptr)
{
	//Player not set yet. Will set with setPlayer();
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
{	//If the neutral player was attacked, the player is now aggressive!
	if(*neutral._wasAttacked) {
		out << *neutral._agressiveStrategy;
	}
	else {
		out << "Neutral strategy: Computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player." << std::endl;
		out << "Player info:" << std::endl;
		out << *neutral.p;
	}
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
	_wasAttacked = new bool(false);
	_agressiveStrategy = new AggressivePlayerStrategy();
}

NeutralPlayerStrategy::~NeutralPlayerStrategy()
{
	delete _wasAttacked;
	delete _agressiveStrategy;
}

void NeutralPlayerStrategy::issueOrder(GameEngine* gameEngine, string orderType)
{
	//If player was attacked, permanently turn _wasAttacked to true
	if (p->wasAttacked())
		*_wasAttacked = true;

	//No orders to issue UNLESS attacked
	if (*_wasAttacked) {
		if (_agressiveStrategy->getPlayer() == nullptr)
			_agressiveStrategy->setPlayer(p);
		else
			_agressiveStrategy->issueOrder(gameEngine, orderType); //We will now let the aggressive strategy issue orders
	}
}

vector<Territory*> NeutralPlayerStrategy::toAttack(Territory* t)
{
	//If player was attacked, permanently turn _wasAttacked to true
	if (p->wasAttacked())
		*_wasAttacked = true;

	//Don't attack UNLESS we were attacked at some point in which case we delegate to _agressiveStrategy
	if (*_wasAttacked) {
		return _agressiveStrategy->toAttack(t);
	} else
	//No territories to attack
	return vector<Territory*>();
}

vector<Territory*> NeutralPlayerStrategy::toDefend(Territory* t)
{
	//If player was attacked, permanently turn _wasAttacked to true
	if (p->wasAttacked())
		*_wasAttacked = true;

	//Don't defend UNLESS we were attacked at some point in which case we delegate to _agressiveStrategy
	if (*_wasAttacked) {
		return _agressiveStrategy->toDefend(t);
	}
	else
		//No territories to defend
		return vector<Territory*>();
}

NeutralPlayerStrategy::NeutralPlayerStrategy(Player* p) : NeutralPlayerStrategy()
{
	setPlayer(p);
	_agressiveStrategy->setPlayer(p);
}

NeutralPlayerStrategy::NeutralPlayerStrategy(const NeutralPlayerStrategy& other) : PlayerStrategy(other)
{
	this->_wasAttacked = new bool(*other._wasAttacked);
	this->_agressiveStrategy = new AggressivePlayerStrategy(*other._agressiveStrategy);
}

NeutralPlayerStrategy& NeutralPlayerStrategy::operator=(const NeutralPlayerStrategy& rhs)
{
	setPlayer(rhs.p);
	this->_wasAttacked = new bool(*rhs._wasAttacked);
	this->_agressiveStrategy = new AggressivePlayerStrategy(*rhs._agressiveStrategy);
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

void AggressivePlayerStrategy::issueOrder(GameEngine* gameEngine, string orderType)
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

void BenevolentPlayerStrategy::issueOrder(GameEngine* gameEngine, string orderType)
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

void CheaterPlayerStrategy::issueOrder(GameEngine* gameEngine, string orderType)
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

void HumanPlayerStrategy::issueOrder(GameEngine* gameEngine, string orderType)
{
	if (orderType == "deploy")
		gameEngine->deploy_phase(*p);
	else if (orderType == "diplomacy")
		diplomacyHelper(gameEngine);
	else if (orderType == "airlift")
		airliftHelper();
	else if (orderType == "blockade")
		blockadeHelper();
	else if (orderType == "bomb")
		bombHelper();
	else if (orderType == "advance")
		advanceHelper();
	else
		std::cout << "~~Invalid order issued~~" << std::endl;
}

vector<Territory*> HumanPlayerStrategy::toAttack(Territory* t)
{
	vector<Territory*> neighbors;

	for (Territory* terr : t->get_neighbors()) {
		if (terr->get_claimant() != p) {
			neighbors.push_back(terr);
		}
	}
	return neighbors;
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

void HumanPlayerStrategy::log(string str)
{
	std::cout << "\n>> " << str << std::endl;
}

void HumanPlayerStrategy::input()
{
	std::cout << "> " << std::endl;
}

void HumanPlayerStrategy::advanceHelper()
{
	// Pick a territory from all the territories
	int count = 0;

	cout << *p->getName() << endl;
	cout << "Pick territory of choice: " << endl;
	for (Territory* t : p->get_territories()) {
		cout << "\n" << to_string(count) << ": " << t->get_name() << " [" << t->get_stationed_army() << "]";
		count++;
	}

	int option;

	do {
		input();

			std::cin >> option;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			option = -1;
		}

		if (option > count - 1 || option < 0)
			cout << "Please enter a number between 0 and " << count - 1 << endl;

	} while (option > count - 1 || option < 0);

	count = 0;
	cout << "Please choose a territory to advance to: " << endl;
	for (Territory* t : p->get_territories()[option]->get_neighbors()) {
		cout << "\n" + to_string(count) + ": " + t->get_name();
		count++;
	}

	int option2;

	do {
		input();

			std::cin >> option2;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			option = -1;
		}

		if (option2 > count - 1 || option2 < 0)
			cout << "Please enter a number between 0 and " << count - 1 << endl;

	} while (option2 > count - 1 || option2 < 0);
	Advance* advanceOrder = new Advance(&(*p), p->get_territories()[option], p->get_territories()[option]->get_neighbors()[option2]);
	//Attach the first observer to the order.
	advanceOrder->attach(p->getOrdersList()->getObservers().at(0));
	p->getOrdersList()->addOrder(advanceOrder);
}

void HumanPlayerStrategy::airliftHelper()
{
	log("Airlift");

	// Pick a territories from all the territories
	int count = 0;
	int option[2]; //option 0 is souce and 1 is destination
	cout << *p->getName() << endl;

	for (size_t i = 0; i < 2; i++) {

		cout << "Select territory " << ((i == 0) ? "SOURCE" : "DESTINATION") << " for airlift : " << endl;

		for (Territory* t : p->get_territories()) {
			cout << "\n" << to_string(count) << ": " << t->get_name() << " [" << t->get_stationed_army() << "]";
			count++;
		}

		do {
			input();

			std::cin >> option[i];

			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(1000, '\n');
				option[i] = -1;
			}

			if (option[i] > count - 1 || option[i] < 0)
				cout << "Please enter a number between 0 and " << count - 1 << endl;

		} while (option[i] > count - 1 || option[i] < 0);

		count = 0;
	}
	Airlift* airliftOrder = new Airlift(p->get_territories()[option[0]], p->get_territories()[option[1]]);
	airliftOrder->attach(p->getOrdersList()->getObservers().at(0));
	p->getOrdersList()->addOrder(airliftOrder);
}

void HumanPlayerStrategy::bombHelper()
{
	log("Bomb");

	// Pick a territories from all the territories
	int count = 0;
	int option;// destination
	cout << *p->getName() << endl;


	cout << "Select territory DESTINATION to Bomb : " << endl;

	for (Territory* t : Map::get_instance()->get_territories()) {
		cout << "\n" << to_string(count) << ": " << t->get_name() << " [" << t->get_stationed_army() << "]";
		count++;
	}

	do {
		input();

		std::cin >> option;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			option = -1;
		}

		if (option > count - 1 || option < 0)
			cout << "Please enter a number between 0 and " << count - 1 << endl;

		else if (Map::get_instance()->get_territories()[option]->get_claimant() == &(*p)) {

			cout << "You can't bomb yourself" << endl;
			option = -1;
		}

	} while (option > count - 1 || option < 0);

	Bomb* bombOrder = new Bomb(Map::get_instance()->get_territories()[option]);
	bombOrder->attach(p->getOrdersList()->getObservers().at(0));

	p->getOrdersList()->addOrder(bombOrder);
}

void HumanPlayerStrategy::blockadeHelper()
{
	log("Blockade");

	// Pick a territories from all the territories
	int count = 0;
	int option;// destination
	cout << *p->getName() << endl;


	cout << "Select territory DESTINATION to Bomb : " << endl;

	for (Territory* t : p->get_territories()) {
		cout << "\n" << to_string(count) << ": " << t->get_name() << " [" << t->get_stationed_army() << "]";
		count++;
	}

	do {
		input();

		std::cin >> option;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			option = -1;
		}

		if (option > count - 1 || option < 0)
			cout << "Please enter a number between 0 and " << count - 1 << endl;


	} while (option > count - 1 || option < 0);

	Blockade* blockadeOrder = new Blockade(p->get_territories()[option]);
	blockadeOrder->attach(p->getOrdersList()->getObservers().at(0));

	p->getOrdersList()->addOrder(blockadeOrder);
}

void HumanPlayerStrategy::diplomacyHelper(GameEngine* gameEngine)
{
	log("Diplomacy");

	// Pick a territories from all the territories
	int count = 0;
	int option;// destination
	cout << *p->getName() << endl;


	cout << "Select Player to Negotiate : " << endl;

	for (Player* p : gameEngine->get_players()) {
		cout << "\n" << to_string(count) << ": " << *p->getName();
		count++;
	}

	do {
		input();

		std::cin >> option;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			option = -1;
		}

		if (option > count - 1 || option < 0)
			cout << "Please enter a number between 0 and " << count - 1 << endl;

	} while (option > count - 1 || option < 0);

	Negotiate* negotiateOrder = new Negotiate(&(*p), gameEngine->get_players()[option]);
	negotiateOrder->attach(p->getOrdersList()->getObservers().at(0));

	p->getOrdersList()->addOrder(negotiateOrder);
}
