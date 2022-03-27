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

void Player::issueOrder() { //no specifications to what it takes in or creates
#define DEPLOY "deploy"
#define ADVANCE "advance"
#define AIRLIFT "airlift"
#define BOMB "bomb"
#define NEGOTIATE "negotiate"
#define BLOCKADE "blockade"

#define UPPERLIMIT 6

    int option;
    try {
        do {
            Hand * hand = new Hand(*this->_hand);
            std::cout << "Please enter a number between 1 to " << UPPERLIMIT << "."
                "\n 1. " << DEPLOY
                "\n 2. " << ADVANCE
                "\n 3. " << AIRLIFT
                "\n 4. " << BOMB
                "\n 5. " << NEGOTIATE 
                "\n 6. " << BLOCKADE
                "\n> ";

            std::cin >> option;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                option = -1;
            }
        } while (option > UPPERLIMIT || option < 1);

        switch (option)
        {
        case 1:

            this->_listOfOrders->addOrder(new Deploy());
            break;

        case 2:
            this->_listOfOrders->addOrder(new Advance());
            break;

        case 3:

            for (auto card : _hand->getCards()) {
                if (card->getType() == "Airlift") { this->_listOfOrders->addOrder(new Airlift()); }
                else {
                    cout << "Player " << getName() << " does not have an airlift card" << endl;
                }
            }

            break;

        case 4:
            for (auto card : _hand->getCards()) {
                if (card->getType() == "Bomb") { this->_listOfOrders->addOrder(new Bomb());; }
                else {
                cout << "Player " << getName() << " does not have a bomb card" << endl;
                }
            }
            
            break;

        case 5:

            for (auto card : _hand->getCards()) {
                if (card->getType() == "Negotiate") { this->_listOfOrders->addOrder(new Negotiate()); }
                else {
                cout << "Player " << getName() << " does not have a negotiate card" << endl;
                }
            }

            break;

        case 6:
            bool has_card4 = false;
            for (auto card : _hand->getCards()) {
                if (card->getType() == "Blockade") { this->_listOfOrders->addOrder(new Blockade()); }
                else {
                cout << "Player " << getName() << " does not have a blockade card" << endl;
                }
            }
           
            break;
        }
    }
    catch (runtime_error e) {
        std::cout << "ERROR: " << e.what() << std::endl;

    }
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
