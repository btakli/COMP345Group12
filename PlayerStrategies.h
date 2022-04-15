#pragma once
#include <iostream>
#include <vector>
#include <string>

//Forward declaration
class Player;
class Order;
class Territory;
class GameEngine;

using std::vector;
using std::string;


//PlayerStrategy abstract class, used to set the different player strategies (Neutral, Cheater, Human, Aggressive, Benevolent)
class PlayerStrategy {
public:
	//Default constructor. Player is not pointed to so you need to use setPlayer();
	PlayerStrategy();
	//Destructor
	virtual ~PlayerStrategy();
	//Contains logic to add order to player's list of orders
	virtual void issueOrder(GameEngine* gameEngine, string orderType) = 0;
	//Returns list of territories that can be attacked from t
	virtual vector<Territory*> toAttack(Territory* t) = 0;
	//Returns a list of territories that can be defended by t
	virtual vector<Territory*> toDefend(Territory* t) = 0;
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const PlayerStrategy& playerStrategy);
	//clone method
	virtual PlayerStrategy* clone() = 0;
	//Set player pointer to a new player. Useful for copy constructor of player;
	void setPlayer(Player* newPlayer);
	//Get pointer to Player p. Returns null if there is no player pointed to.
	Player* getPlayer();
	
protected:
	//Protected constructor, we should not be able to construct this
	PlayerStrategy(Player* p);
	//Copy constructor
	PlayerStrategy(const PlayerStrategy& other);
	//Assignment operator
	PlayerStrategy& operator=(const PlayerStrategy& rhs);
	//Pointer to player
	Player* p;
};

//Forward declaration
class AggressivePlayerStrategy;
//Neutral player: computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player.
class NeutralPlayerStrategy : public PlayerStrategy {
public:
	//Default constructor. Player is not pointed to so you need to use setPlayer();
	NeutralPlayerStrategy();
	//Destructor
	virtual ~NeutralPlayerStrategy();
	//Contains logic to add order to player's list of orders
	virtual void issueOrder(GameEngine* gameEngine, string orderType);
	//Returns list of territories that can be attacked from t
	virtual vector<Territory*> toAttack(Territory* t);
	//Returns list of territories that can be defended by t
	virtual vector<Territory*> toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const NeutralPlayerStrategy& neutral);
	//Constructor
	NeutralPlayerStrategy(Player* p);
	//Copy constructor
	NeutralPlayerStrategy(const NeutralPlayerStrategy& other);
	//Assignment operator
	NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& rhs);
	//clone method
	virtual NeutralPlayerStrategy* clone();
private:
	//boolean dictating whether at some point this neutral player was attacked
	bool* _wasAttacked;
	//We become aggressive if attacked! Delegate all actions here if so.
	AggressivePlayerStrategy* _agressiveStrategy;
};
//Aggressive player: computer player that focuses on attack (deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore).
class AggressivePlayerStrategy : public PlayerStrategy {
public:
	//Default constructor. Player is not pointed to so you need to use setPlayer();
	AggressivePlayerStrategy();
	//Destructor
	virtual ~AggressivePlayerStrategy();
	//Contains logic to add order to player's list of orders
	virtual void issueOrder(GameEngine* gameEngine, string orderType);
	//Returns list of territories that can be attacked from t
	virtual vector<Territory*> toAttack(Territory* t);
	//Returns list of territories that can be defended by t
	virtual vector<Territory*> toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const AggressivePlayerStrategy& aggressive);
	//Constructor
	AggressivePlayerStrategy(Player* p);
	//Copy constructor
	AggressivePlayerStrategy(const AggressivePlayerStrategy& other);
	//Assignment operator
	AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& rhs);
	//clone method
	virtual AggressivePlayerStrategy* clone();
private:
	//Finds the strongest territory (one with the most deployed armies). If there is a tie, return any of them.
	Territory* strongestTerritory();
};

//Benevolent player: computer player that focuses on protecting its weak countries (deploys or advances armies on its weakest countries, never advances to enemy territories).
class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	//Default constructor. Player is not pointed to so you need to use setPlayer();
	BenevolentPlayerStrategy();
	//Destructor
	virtual ~BenevolentPlayerStrategy();
	//Contains logic to add order to player's list of orders
	//used exclusively to deploy on the weakest territories, and then spread them onto remaining weakest countries using advance
	virtual void issueOrder(GameEngine* gameEngine, string orderType);
	//Returns list of territories that can be attacked from t
	//not needed for this strategy
	virtual vector<Territory*> toAttack(Territory* t);
	//Returns list of territories that can be defended by t
	virtual vector<Territory*> toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const BenevolentPlayerStrategy& benevolent);
	//Constructor
	BenevolentPlayerStrategy(Player* p);
	//Copy constructor
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& other);
	//Assignment operator
	BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& rhs);
	//clone method
	virtual BenevolentPlayerStrategy* clone();
	
private:
	//---------
	//Functions specific to Benevolent player strategy
	//---------
	// 

	//returns a pointer weakest territory owned by player
	Territory* getWeakest();
	//Updates the _weakest pointer
	void findWeakest();
	//points to players weakest territory
	Territory* _weakest;

};

//Cheater player: computer player that automatically conquers all territories that are adjacent to its own territories(only once per turn).
class CheaterPlayerStrategy : public PlayerStrategy {
public:
	//Default constructor. Player is not pointed to so you need to use setPlayer();
	CheaterPlayerStrategy();
	//Destructor
	virtual ~CheaterPlayerStrategy();
	//Contains logic to add order to player's list of orders
	virtual void issueOrder(GameEngine* gameEngine, string orderType);
	//Returns list of territories that can be attacked from t
	virtual vector<Territory*> toAttack(Territory* t);
	//Returns list of territories that can be defended by t
	virtual vector<Territory*> toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const CheaterPlayerStrategy& cheater);
	//Constructor
	CheaterPlayerStrategy(Player* p);
	//Copy constructor
	CheaterPlayerStrategy(const CheaterPlayerStrategy& other);
	//Assignment operator
	CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy& rhs);
	//clone method
	virtual CheaterPlayerStrategy* clone();
};

//Human player: requires user interactions to make decisions.
class HumanPlayerStrategy : public PlayerStrategy {
public:
	//Default constructor. Player is not pointed to so you need to use setPlayer();
	HumanPlayerStrategy();
	//Destructor
	virtual ~HumanPlayerStrategy();
	//Contains logic to add order to player's list of orders
	virtual void issueOrder(GameEngine* gameEngine, string orderType);
	//Returns list of territories that can be attacked from t
	virtual vector<Territory*> toAttack(Territory* t);
	//Returns list of territories that can be defended by t
	virtual vector<Territory*> toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const HumanPlayerStrategy& human);
	//Constructor
	HumanPlayerStrategy(Player* p);
	//Copy constructor
	HumanPlayerStrategy(const HumanPlayerStrategy& other);
	//Assignment operator
	HumanPlayerStrategy& operator=(const HumanPlayerStrategy& rhs);
	//clone method
	virtual HumanPlayerStrategy* clone();
private:
	//Formatted output for the console
	void log(std::string str);
	//Formatted output for an input to the console "> *insert text*"
	void input();
	//Deploy helper for IssueOrder
	void advanceHelper();
	//Airlift helper for IssueOrder
	void airliftHelper();
	//Bomb helper for IssueOrder
	void bombHelper();
	//Blockade helper for IssueOrder
	void blockadeHelper();
	//Diplomacy helper for IssueOrder
	void diplomacyHelper(GameEngine* gameEngine);
};