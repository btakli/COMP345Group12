#include <vector>
#include <iostream> 
#include "Player.h"
using std::string;
using std::vector;
using std::cout;

int Player::s_index = 0;

Player::Player() {
    this->_index = new int(s_index++);
    this->_name = new string("player");
    this->_collection = new vector<Territory*> {};
    this->_hand  = new Hand();
    this->_listOfOrders = new OrdersList();
}

Player::Player(string name) {
    this->_index = new int(s_index++);
    this->_name = new string(name);
    this->_collection = new vector<Territory*>;
    this->_hand = new Hand();                         
    this->_listOfOrders = new OrdersList();
}

Player::Player(string name, vector<Territory*> collection) {
    this->_index = new int(s_index++);
    this->_name = new string(name);
    this->_collection = new vector<Territory*>;
    for (auto territory : collection) {
        this->_collection->push_back(territory);
    }
    this->_hand = new Hand();                         
    this->_listOfOrders = new OrdersList();
}

Player::Player(string name, vector<Territory*> collection, Hand* hand, OrdersList * listOfOrders) {
    this->_index = new int(s_index++);
    this->_name = new string(name);
    this->_collection = new vector<Territory*>;
    for (auto territory : collection) {
        this->_collection->push_back(territory);
    }
    this->_hand = new Hand(*hand);                         
    this->_listOfOrders = new OrdersList(*listOfOrders);
}

Player::~Player() {
    delete _name;
    delete _collection;
    delete _hand;                          
    delete _listOfOrders;
    delete _index;
}

vector<Territory *>* Player::toDefend() {


    return nullptr;
}

vector<Territory *>* Player::toAttack() {


    return nullptr;
}

int& Player::getIndex() {
    return *_index;
}

void Player::issueOrder() { 

}

void Player::issueOrder(Order *pOrder) {
    this->_listOfOrders->addOrder(pOrder);
}

Hand* Player::getHand() {
    return this->_hand;
}

OrdersList* Player::getOrdersList()
{
    return this->_listOfOrders;
}

string* Player::getName()
{
    return this->_name;
}

vector<Territory*>& Player::get_territories() {
    return *_collection;
}

Player::Player( const Player &p){
    this->_index = new int(*p._index);
    this->_name = new string(*(p._name));
    for (auto territory : *p._collection) {
        this->_collection->push_back(territory); //Shallow copy because the territory should not be recreated
    }
    this->_hand = new Hand(*p._hand);                          //methods need to be implemented in Hand and OrdersList
    this->_listOfOrders = new OrdersList(*p._listOfOrders);
}


Player& Player::operator=(const Player& p) {
    this->_index = new int(*p._index);
    this->_name = new string(*p._name);
    this->_collection = new std::vector<Territory*>;
    for (auto territory : *p._collection) {
        this->_collection->push_back(territory); //Shallow copy because the territory should not be recreated
    }
    this->_hand = new Hand(*p._hand);                          //methods need to be implemented in Hand and OrdersList
    this->_listOfOrders = new OrdersList(*p._listOfOrders);
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << "Player: " + *player._name + " \n";
    out << "Collection: \n";
    for (const auto& territory : *player._collection)
        out << "\t Territory: " + territory->get_name() + "\n ";
    out << *player._hand;
    out << *player._listOfOrders;
    return out;
}
