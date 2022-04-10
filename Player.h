#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "LoggingObserver.h"
using std::string;
using std::vector;

//Forward declaration
class Territory;
class PlayerStrategy;
class GameEngine;

//Class for players
class Player {
public:
    //Basic constructor
    Player();

    //Constructor with player name
    Player(string name, Deck* deck);

    //LEGACY: constructor without observer or strategy
    Player(string name, vector<Territory*> collection);
    //LEGACY: Constructor with logging observer which will be passed to list of orders
    Player(string name, Deck* deck, LogObserver* lo);
    //Constructor with logging observer which will be passed to list of orders. Takes in Player Strategy too which is necessary.
    Player(string name, Deck* deck, LogObserver* lo, PlayerStrategy* ps);
    //LEGACY: Constructor taking in string for name, list of pointers to territory, Hand pointer and OrdersList pointer
    Player(string name, Deck* deck, std::vector<Territory*> collection, Hand* hand, OrdersList* listOfOrders);
    //Add a territory to defend
    vector<Territory*> toDefend(Territory *t);
    //ad a territory to attack
    vector<Territory*> toAttack(Territory *t);
    //Creates new order and adds it to _listOfOrders. Contains all the logic needed for decisions
    void issueOrder(GameEngine* gameEngine, string orderType);
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
    //Player draws a card from the deck
    void drawCard();
    //Get all territories the Player owns.
    vector<Territory*>& get_territories();

    //Sets the player's strategy to a new one
    void setStrategy(PlayerStrategy* ps);

    //Getter for _wasAttacked boolean
    bool wasAttacked();
    //Setter for _wasAttacked boolean
    void setWasAttacked(bool value);
    

private:
    //Boolean showing if the Player was attacked
    bool* _wasAttacked;
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
    //Strategy for the player
    PlayerStrategy* _ps;
    //The main deck, player should have a pointer to it but NOT delete it!
    Deck* _deck;
};



