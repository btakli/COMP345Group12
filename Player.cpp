#include <vector>
#include <iostream> 

#include "Player.h"


Player::Player() {

}

Player::Player(std::vector<Territory>* collection, std::vector<Country> * hand, std::vector<OrdersList>* listOfOrders)   //Replace Country with Cards
{

}

std::vector<Territory>* Player::toDefend(){
    return nullptr;
}
    
std::vector<Territory>* Player::toAttack(){
    return nullptr;
}

/*    
void Player::issueOrder(){
    Order * ord = new Order();
    add_to_ListOfOrder(ord);

}

void Player::add_to_ListOfOrder(Order ord){


}*/

Player::Player(Player& p){                      //copy constructor seems shallow
    this->_collection = p._collection;
    this -> _hand = p._hand;
    this -> _listOfOrders = p._listOfOrders;
}

Player& Player:: operator =(const Player &p){    //Assignment operator
    this->_collection = p._collection;
    this -> _hand = p._hand;
    this -> _listOfOrders = p._listOfOrders;
    return *this;

}
Player::~Player(){                              //Destructor
    delete _collection;
    delete _hand;
    delete _listOfOrders;
    this -> _collection = nullptr;
    this -> _hand = nullptr;
    this -> _listOfOrders = nullptr;
    delete this;
}

void Player::set_collection(std::vector<Territory>* col){
    this -> _collection = col;
}

std::vector<Territory> Player::get_collection(){
    return *_collection;

}

void Player::set_hand(std::vector<Territory>*){

}

std::vector<Territory> Player::get_hand(){
    return *_hand;
}   

void Player::set_listOfOrders(std::vector<OrdersList>*){

}

std::vector<OrdersList> Player::get_listOfOrders(){
    return *_listOfOrders;
}


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