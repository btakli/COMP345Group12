#pragma once
#include <iostream>

//Forward declaration
class Player;
class Order;
class Territory;
//PlayerStrategy abstract class, used to set the different player strategies (Neutral, Cheater, Human, Aggressive, Benevolent)
class PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder) = 0;
	//add a territory to attack
	virtual void toAttack(Territory* t) = 0;
	//Add a territory to defend
	virtual void toDefend(Territory* t) = 0;
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const PlayerStrategy& playerStrategy);
	//clone method
	virtual PlayerStrategy* clone() = 0;
	//Set player pointer to a new player. Useful for copy constructor of player;
	void setPlayer(Player* newPlayer);
	
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
//Neutral player: computer player that never issues any order. If a Neutral player is attacked, it becomes an Aggressive player.
class NeutralPlayerStrategy : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
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
};
//Aggressive player: computer player that focuses on attack (deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore).
class AggressivePlayerStrategy : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
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
};

//Benevolent player: computer player that focuses on protecting its weak countries (deploys or advances armies on its weakest countries, never advances to enemy territories).
class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
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
};

//Cheater player: computer player that automatically conquers all territories that are adjacent to its own territories(only once per turn).
class CheaterPlayerStrategy : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
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
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
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
};


