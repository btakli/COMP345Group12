#pragma once


#include <list>
#include <vector>
#include <iostream>

#include "Map.h"
#include "Orders.h"

using namespace std;

class Player
{
public:
    Player();
    Player(std::vector<Territory>* collection, std::vector<Country> * hand, std::vector<OrdersList>* listOfOrders);   //Replace Country with Cards
    std::vector<Territory>* toDefend();
    std::vector<Territory>* toAttack();
    void issueOrder();

    Player(Player& p);                      //copy constructor
    Player& operator =(const Player& e);    //Assignment operator
    ~Player();                              //Destructor


    void set_collection(std::vector<Territory>* collection);
    std::vector<Territory> get_collection();

    void add_to_collection(Territory* addTerr);

    void set_hand(std::vector<Territory>* hand);
    std::vector<Territory> get_hand();

    void add_to_hand(Territory* addHand);

    void set_listOfOrders(std::vector<OrdersList>*);
    std::vector<OrdersList> get_listOfOrders();

    void add_to_ListOfOrder (Order* addOrd);
private:
    std::vector<Territory>* _collection;
    std::vector<Territory>* _hand;
    std::vector<OrdersList>* _listOfOrders;

//player owns collection of territories
//player owns a hand of Cards
//player has their own list of orders to be createdd andexcecuted in the current term

//player methods: for now, have them return arbitrary lists
    //toDefend() -- return a list of territories to be defended
    //toAttack() -- return a list of territories to attack
    //issueOrder() -- creates an Order object and puts it in the players list of orders

//All data members of user-defined class type must be of pointer type. 

};


