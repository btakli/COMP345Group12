#pragma once
#include <string>

#include <vector>
#include <iostream>

#include "Map.h"
#include "Orders.h"



class Player {
public:
    Player();
    Player(string name);   //Replace Country with Cards
    Player(string name, vector<Territory*> collection, vector<Territory*> hand, OrdersList* listOfOrders);   //Replace Country with Cards
    vector<Territory*> toDefend();


    vector<Territory*> toAttack();
    void issueOrder();

    Player(Player& p);                      //copy constructor
    Player& operator =(const Player& e);    //Assignment operator
    ~Player();                              //Destructor


    void set_collection(vector<Territory*> collection);
    vector<Territory*> get_collection();

    void add_to_collection(Territory* addTerr);

    void set_hand(vector<Territory*> hand);
    vector<Territory*> get_hand();

    void add_to_hand(Territory* addHand);

    void set_listOfOrders(vector<OrdersList*>);
    OrdersList* get_listOfOrders();

    void add_to_ListOfOrder (Order* addOrd);

    friend ostream &operator<<(ostream &out, const Player &player);
    string name;
    vector<Territory*> collection;
    vector<Territory*> hand;
    OrdersList* listOfOrders;

//player owns collection of territories
//player owns a hand of Cards
//player has their own list of orders to be createdd andexcecuted in the current term

//player methods: for now, have them return arbitrary lists
    //toDefend() -- return a list of territories to be defended
    //toAttack() -- return a list of territories to attack
    //issueOrder() -- creates an Order object and puts it in the players list of orders

//All data members of user-defined class type must be of pointer type. 

};


