#pragma once
#include <string>

#include <vector>
#include <iostream>

#include "Cards.h"
#include "Map.h"
#include "Orders.h"


class Territory;
class Card;
class Hand;
class Order;


class Player {
public:
    Player();
    Player(string name, vector<Territory*> * collection, Hand* hand, OrdersList* listOfOrders);   //Constructor
    vector<Territory*> toDefend();  //methods to implement for player
    vector<Territory*> toAttack();
    void issueOrder();

    Player(Player& p);                      //copy constructor
    Player& operator =(const Player& e);    //Assignment operator
    ~Player();                              //Destructor

    //returns name of Player
    string* get_name();
    //set players name
    void set_name(string * name);
    //set collection of territories. pointer pointing to vector holding pointers pointing to a Territory
    void set_collection(vector<Territory*>* collection);
    //returns collection of Territory belonging to Player
    vector<Territory*>* get_collection();
    //add a single territory  to the collection vector
    void add_to_collection(Territory* addTerr);
    void remove_from_collection(Territory* delTerr);
    Hand* get_hand();

    OrdersList* get_listOfOrders();

    void add_to_ListOfOrder (Order* addOrd);

    friend ostream &operator<<(ostream &out, const Player &player);

private:
    string* _name;
    vector<Territory*>* _collection;
    Hand* _hand;
    OrdersList* _listOfOrders;
};
//player owns collection of territories
//player owns a hand of Cards
//player has their own list of orders to be createdd andexcecuted in the current term

//player methods: for now, have them return arbitrary lists
    //toDefend() -- return a list of territories to be defended
    //toAttack() -- return a list of territories to attack
    //issueOrder() -- creates an Order object and puts it in the players list of orders

//All data members of user-defined class type must be of pointer type. 



