#include <vector>
#include <iostream> 
#include "Player.h"
#include "PlayerStrategies.h"
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
    this->_ps = nullptr; //Strategy not set in this constructor!
}

Player::Player(string name, Deck* deck) {
    this->_deck = deck;
    this->_index = new int(s_index++);
    this->_name = new string(name);
    this->_collection = new vector<Territory*>;
    this->_hand = new Hand();                         
    this->_listOfOrders = new OrdersList();
    this->_ps = nullptr; //Strategy not set in this constructor!
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
    this->_ps = nullptr; //Strategy not set in this constructor!
}

void Player::drawCard() {
    cout << "Draw a card" << endl;
    _hand->addCard(_deck->draw());
}

Player::Player(string name, vector<Territory*> collection, LogObserver* lo): Player(name,collection)
{
    _listOfOrders->attach(lo);
}

Player::Player(string name, vector<Territory*> collection, LogObserver* lo, PlayerStrategy* ps): Player(name, collection, lo)
{
    this->_ps = ps;
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

    this->_ps = nullptr; //Strategy not set in this constructor!
}

Player::~Player() {
    delete _name;
    delete _collection;
    delete _hand;                          
    delete _listOfOrders;
    delete _index;
}

vector<Territory*> Player::toDefend(Territory* source) {
    vector<Territory*> neighbors;

    for (Territory* t : source->get_neighbors()) {
        if (t->get_claimant() == this) {
            neighbors.push_back(t);
        }
    }

    return neighbors;
}

vector<Territory*> Player::toAttack(Territory* source) {
    vector<Territory*> neighbors;

    for (Territory* t : source->get_neighbors()) {
        if (t->get_claimant() != this) {
            neighbors.push_back(t);
        }
    }

    return neighbors;
}

int& Player::getIndex() {
    return *_index;
}

void Player::issueOrder() { 

}

void Player::issueOrder(Order *pOrder) {
    if (_ps)
        _ps->issueOrder(pOrder);
    else
        std::cout << "No strategy set for Player " << this->_name << ". Are you sure you used the right constructor?" << std::endl;
    //this->_listOfOrders->addOrder(pOrder); //Old way of doing it
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

Player::Player(const Player &p){
    this->_index = new int(*p._index);
    this->_name = new string(*(p._name));
    this->_collection = new vector<Territory*>();

    this->_ps = p._ps->clone();
    this->_ps->setPlayer(this);

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

    this->_ps = p._ps->clone();
    this->_ps->setPlayer(this);

    return *this;
}

std::ostream& operator<<(std::ostream& out, const Player& player) {
    out << "Player: " + *player._name + " \n";
    out << "Collection: \n";
    for (const auto& territory : *player._collection)
        out << "\t Territory: " + territory->get_name() + "\n ";
    out << "To attack \n";
    out << *player._hand;
    out << *player._listOfOrders;
    return out;
}


