#include <vector>
#include <iostream> 

#include "Player.h"


Player::Player() {
    this->name = "";
    this->collection = vector<Territory *> {};
    this->hand = vector<Territory*> {};
//    this->listOfOrders = new OrdersList();
}

Player::Player(string name, vector<Territory *> collection, vector<Territory *> hand, OrdersList *listOfOrders) {
    this->name = name;
    this->collection = collection;
    this->hand = hand;
//    this->listOfOrders = listOfOrders;
}

Player::~Player() {
    for (auto territory : collection) {
        delete territory;
    }
    collection.clear();
    for (auto card: hand) {
        delete(card);
    }
    hand.clear();
}



