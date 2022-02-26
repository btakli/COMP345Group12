#pragma once
#include <string>

#include <vector>
#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
using std::string;
using std::vector;

/*
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
*/
class Territory;

//Forward declaration
class Player;
//Class for players
class Player {
public:
    //Basic constructor
    Player();
    //Constructor taking in string for name, list of pointers to territory, Hand pointer and OrdersList pointer
    Player(string name, std::vector<Territory*> collection, Hand* hand, OrdersList* listOfOrders);
    //prints and returns a list of territories to defend
    vector<Territory*>* toDefend();
    //prints and returns a list of territories to attack
    vector<Territory*>* toAttack();
    //Creates new order and adds it to _listOfOrders
    void issueOrder();
    //Copy constructor
    Player(const Player& p);
    //assignment operator
    Player& operator =(const Player& e);
    //destructor
    ~Player();
    //stream insertion operator overload for Player
    friend ostream &operator<<(ostream &out, const Player &player);

private:
    //player name
    string* _name;
    //collection of territories
    vector<Territory*>* _collection;
    //Hand object holds cards
    Hand* _hand;
    //OrdersList object holds orders
    OrdersList* _listOfOrders;
};



