#include <vector>
#include <iostream> 
#include "Player.h"
#include "PlayerStrategies.h"
using std::string;
using std::vector;
using std::cout;

int Player::s_index = 0;

Player::Player() : Player("player", nullptr, nullptr, nullptr) {

}

Player::Player(string name, Deck* deck): Player(name, deck, nullptr, nullptr) {
    
}

Player::Player(string name, vector<Territory*> collection) : Player(name,nullptr) {
    for (auto territory : collection) {
        this->_collection->push_back(territory);
    }
}

Player::Player(string name, Deck* deck, LogObserver* lo): Player(name,deck,lo,nullptr)
{
}

Player::Player(string name, Deck* deck, LogObserver* lo, PlayerStrategy* ps) //This is the main constructor you should use!
{
    this->_index = new int(s_index++);
    this->_name = new string(name);
    this->_deck = deck;
    this->_collection = new vector<Territory*>();
    this->_hand = new Hand();
    this->_listOfOrders = new OrdersList();
    this->_ps = ps;
    this->_wasAttacked = new bool(false);

    //Auto set the default strategy to human
    if (!_ps) {
        _ps = new HumanPlayerStrategy();
        _ps->setPlayer(this);
    }
    if (_ps)
        _ps->setPlayer(this);

    if (lo)
        _listOfOrders->attach(lo);
    else
        cout << "~~Note: No LogObserver is attached to the list of orders of player \"" << *_name << "\"~~" << endl;
}

Player::Player(string name, Deck* deck, vector<Territory*> collection, Hand* hand, OrdersList * listOfOrders): Player(name,collection) {
    this->_deck = deck;                     
    this->_listOfOrders = new OrdersList(*listOfOrders);
}

Player::~Player() {
    delete _name;
    delete _collection;
    delete _hand;                          
    delete _listOfOrders;
    delete _index;
    delete _wasAttacked;
}

void Player::drawCard() {
    cout << "Draw a card" << endl;
    _hand->addCard(_deck->draw());
}

vector<Territory*> Player::toDefend(Territory* source) {
    if (_ps)
        return _ps->toDefend(source);
    else
        std::cout << "~~No strategy set for Player " << this->_name << ". Are you sure you used the right constructor?~~" << std::endl;
    return vector<Territory*>();
}

vector<Territory*> Player::toAttack(Territory* source) {
    if (_ps)
        return _ps->toAttack(source);
    else
        std::cout << "~~No strategy set for Player " << this->_name << ". Are you sure you used the right constructor?~~" << std::endl;
    return vector<Territory*>();
}

int& Player::getIndex() {
    return *_index;
}

void Player::issueOrder(GameEngine* gameEngine, string orderType) { 
    if (_ps)
        _ps->issueOrder(gameEngine, orderType);
    else
        std::cout << "~~No strategy set for Player " << this->_name << ". Are you sure you used the right constructor?~~" << std::endl;
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

void Player::setStrategy(PlayerStrategy* ps)
{
    if (_ps)
        delete _ps;
    this->_ps = ps;

}

bool Player::wasAttacked()
{
    return *_wasAttacked;
}

void Player::setWasAttacked(bool value)
{
    *_wasAttacked = value;
}

void Player::clearPlayerBetweenRounds()
{
    getHand()->clearHand();
    get_territories().clear();
    setWasAttacked(false);
    getOrdersList()->clearOrders();
}

Player::Player(const Player &p){
    this->_index = new int(*p._index);
    this->_name = new string(*(p._name));
    this->_deck = new Deck(*p._deck);
    this->_collection = new vector<Territory*>();
    this->_wasAttacked = new bool(*(p._wasAttacked));

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


