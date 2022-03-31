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
class Neutral : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const Neutral& neutral);
	//Constructor
	Neutral(Player* p);
	//Copy constructor
	Neutral(const Neutral& other);
	//Assignment operator
	Neutral& operator=(const Neutral& rhs);
	//clone method
	virtual Neutral* clone();
};
//Aggressive player: computer player that focuses on attack (deploys or advances armies on its strongest country, then always advances to enemy territories until it cannot do so anymore).
class Aggressive : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const Aggressive& aggressive);
	//Constructor
	Aggressive(Player* p);
	//Copy constructor
	Aggressive(const Aggressive& other);
	//Assignment operator
	Aggressive& operator=(const Aggressive& rhs);
	//clone method
	virtual Aggressive* clone();
};

//Benevolent player: computer player that focuses on protecting its weak countries (deploys or advances armies on its weakest countries, never advances to enemy territories).
class Benevolent : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const Benevolent& benevolent);
	//Constructor
	Benevolent(Player* p);
	//Copy constructor
	Benevolent(const Benevolent& other);
	//Assignment operator
	Benevolent& operator=(const Benevolent& rhs);
	//clone method
	virtual Benevolent* clone();
};

//Cheater player: computer player that automatically conquers all territories that are adjacent to its own territories(only once per turn).
class Cheater : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const Cheater& cheater);
	//Constructor
	Cheater(Player* p);
	//Copy constructor
	Cheater(const Cheater& other);
	//Assignment operator
	Cheater& operator=(const Cheater& rhs);
	//clone method
	virtual Cheater* clone();
};

//Human player: requires user interactions to make decisions.
class Human : public PlayerStrategy {
public:
	//takes a pointer to an Order and adds it to the players list of orders
	virtual void issueOrder(Order* pOrder);
	//add a territory to attack
	virtual void toAttack(Territory* t);
	//Add a territory to defend
	virtual void toDefend(Territory* t);
	//Stream insertion operator overload
	friend std::ostream& operator<<(std::ostream& out, const Human& human);
	//Constructor
	Human(Player* p);
	//Copy constructor
	Human(const Human& other);
	//Assignment operator
	Human& operator=(const Human& rhs);
	//clone method
	virtual Human* clone();
};


