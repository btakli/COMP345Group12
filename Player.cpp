#include <vector>
#include <iostream>

#include "Player.h"

Player::Player() {
    this->_name = new string();
    this->_collection = new vector<Territory*> {};
    this->_hand  = new Hand();
    this->_listOfOrders = new OrdersList();
}



Player::Player(string name, vector<Territory*>* collection, Hand* hand, OrdersList * listOfOrders) {
    this->_name = new string(name);
    this->_collection = new vector<Territory*>;
    for (auto territory : *collection) {
        this->_collection->push_back(territory);              //Move territory into _collection
        //territory->claim(*this);                //Claims the territory
    }

    this->_hand = new Hand(*hand);
    this->_listOfOrders = new OrdersList(*listOfOrders);
}

Player::~Player() {
     _name->clear();
    for (auto territory : *_collection) {
        delete territory;
    }
     delete(_hand);
     delete(_listOfOrders);
}


vector<Territory *> Player::toDefend() {
    return {};
}

vector<Territory *> Player::toAttack() {
    return {};
}

void Player::issueOrder() {
    auto *ord = new Order();
    this->_listOfOrders->addOrder(ord);
}


Card::Card(const Card& otherCard)
{
    this->_type = new string(*(otherCard._type));
}
Player::Player( Player &p){
    this->_name = new string(*(p._name));
    for (auto territory : *p._collection) {
        this->_collection->push_back(territory);
        //territory->claim(*this);
    }
    this->_hand = new Hand(*p._hand);
    this->_listOfOrders = p._listOfOrders;
}

Player& Player::operator=(const Player &p) {
    this->_name = new string(*p._name);
    this->_collection = new vector<Territory*>;
    for (auto territory : *p._collection) {
        this->_collection->push_back(territory);
        //territory->claim(*this);
    }
    this->_hand = new Hand(*p._hand);
    this->_listOfOrders = p._listOfOrders;
    return *this;
}

string* Player::get_name(){
    return this->_name;
}

void Player::set_name(string *name){
    this->_name = std::move(name); //used autofill
}

void Player::set_collection(vector<Territory *> *collection) {

}

vector<Territory *> *Player::get_collection() {
    return this->_collection;
}

void Player::add_to_collection(Territory *addTerr) {
    this->_collection->push_back(addTerr);
}
void Player::remove_from_collection(Territory *delTerr) {

}

Hand *Player::get_hand() {
    return nullptr;
}

OrdersList *Player::get_listOfOrders() {
    return nullptr;
}

void Player::add_to_ListOfOrder(Order *addOrd) {

}

ostream &operator<<(ostream &out, const Player &player) {
    out << "Player: " + *player._name;
    return out;
}


