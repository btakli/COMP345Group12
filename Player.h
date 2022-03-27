#pragma once
#include <string>

#include <vector>
#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
using std::string;
using std::vector;

class Territory;

//Forward declaration
class Player;
//Class for players
class Player {
public:
    //Basic constructor
    Player();

    //Constructor with player name
    Player(string name);

    //Constructor for practical use later
    Player(string name, vector<Territory*> collection);
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
    friend std::ostream& operator<<(std::ostream& out, const Player& player);
    //takes a pointer to an Order and adds it to the players list of orders
    void issueOrder(Order *pOrder);
    //Returns players hand
    Hand* getHand();
    //Returns player's OrdersList
    OrdersList* getOrdersList();
    //Returns player's _name
    string* getName();
    
    //Returns player index.
    int& getIndex();

    vector<Territory*>& get_territories();

private:

    //static index
    static int s_index;
    //player index
    int* _index;
    //player name
    string* _name;
    //collection of territories
    vector<Territory*>* _collection;
    //Hand object holds cards
    Hand* _hand;
    //OrdersList object holds orders
    OrdersList* _listOfOrders;
};



