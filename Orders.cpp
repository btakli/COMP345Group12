#include "Orders.h"
#include <vector>
#include <iostream>
using namespace std;


/**
 * Order implementation
 * 
 */

Order::Order() : _type(new string("Default Order")){
    _currentState = new string("Order: Default Order"); //State doesn't change for an order.
}

Order::Order(string type)
{
	this->_type = new string(type);
}

string Order::getType() const
{
	return *(_type);
}

Order::~Order(){ //Destructor
    detachAll(); //Detatch all observers
    delete(_type);
}

Order& Order::operator=(const Order& o){ //Assignment Operator
    this->_type = new string(*(o._type));
	return *this;
}

Order::Order(const Order& o){ //Copy constructor
    this->_type = new string(*(o._type));
}

Order* Order::clone() const 
{
	return new Order(*this);
}

//validate method returns false as order is not considered valid but returns true in the subclasses
bool Order::validate(){  
    return false;
}

void Order::execute(){
    if (validate()) {
        cout << "Order" << endl;
        notify(this); //Call notify to notify observers
    }
   else
      cout << "INVALID ORDER" << endl;
  

}

string Order::stringToLog() {
    return "Order Executed: " + *_currentState;
}

std::ostream& operator<<(std::ostream& description, const Order& o)
{
	return description << "Order of Type: " << o.getType();
}

/**
 * Deploy implementation
 * 
 */


Deploy::Deploy() : Order("deploy"){ //Constructor
    _currentState = new string("Deploy: place some armies on one of the current player's territories."); //State doesn't change for an order.
}

Deploy::~Deploy(){ //Destructor
}

Deploy& Deploy::operator=(const Deploy& dep){ //Assignment Operator
    Order::operator=(dep);
    return *this;
}

Deploy::Deploy(const Deploy& dep){ //Copy constructor

}

Deploy* Deploy::clone() const 
{
	return new Deploy(*this);
}

bool Deploy::validate(){
    return true;
}

void Deploy::execute(){
    if (validate()) {
        cout << "Deploy: place some armies on one of the current player's territories." << endl;
        notify(this); //Call notify to notify observers
    }
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Advance implementation
 * 
 */

Advance::Advance() : Order("advance"){ //Constructor
    _currentState = new string("Advance: move some armies from one of the current player's territories (source) to an adjacent territory (target)."); //State doesn't change for an order.
}

Advance::~Advance(){ //Destructor
}

Advance& Advance::operator=(const Advance& adv){ //Assignment Operator
    Order::operator=(adv);
    return *this;
}

Advance::Advance(const Advance& adv){ //Copy constructor

}

Advance* Advance::clone() const 
{
	return new Advance(*this);
}

bool Advance::validate(){
    return true;
}

void Advance::execute(){
    if (validate()) {
        cout << "Advance: move some armies from one of the current player's territories (source) to an adjacent territory (target)." << endl;
        notify(this); //Call notify to notify observers
    }
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Bomb implementation
 * 
 */

Bomb::Bomb() : Order("bomb"){ //Constructor
    _currentState = new string("Bomb: destroy half of the armies located on an opponent’s territory that is adjacent to one of the current player's territories."); //State doesn't change for an order.
}

Bomb::~Bomb(){ //Destructor
}

Bomb& Bomb::operator=(const Bomb& bmb){ //Assignment Operator
    Order::operator=(bmb);
    return *this;
}

Bomb::Bomb(const Bomb& bmb){ //Copy constructor

}

Bomb* Bomb::clone() const 
{
	return new Bomb(*this);
}

bool Bomb::validate(){
    return true;
}

void Bomb::execute(){
    if (validate()) {
        cout << "Bomb: destroy half of the armies located on an opponent’s territory that is adjacent to one of the current player's territories." << endl;
        notify(this); //Call notify to notify observers
    }
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Blockade implementation
 * 
 */

Blockade::Blockade() : Order("blockade"){ //Constructor
    _currentState = new string("Blockade: triple the number of armies on one of the current player's territories and make it a neutral territory."); //State doesn't change for an order.
}

Blockade::~Blockade(){ //Destructor
}

Blockade& Blockade::operator=(const Blockade& blck){ //Assignment Operator
    Order::operator=(blck);
    return *this;
}

Blockade::Blockade(const Blockade& blck){ //Copy constructor

}

Blockade* Blockade::clone() const 
{
	return new Blockade(*this);
}

bool Blockade::validate(){
    return true;
}

void Blockade::execute(){
    if (validate()) {
        cout << "Blockade: triple the number of armies on one of the current player's territories and make it a neutral territory." << endl;
        notify(this); //Call notify to notify observers
    }
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Airlift implementation
 * 
 */

Airlift::Airlift() : Order("airlift"){ //Constructor
    _currentState = new string("Airlift: advance some armies from one of the current player's territories to any another territory."); //State doesn't change for an order.
}

Airlift::~Airlift(){ //Destructor
}

Airlift& Airlift::operator=(const Airlift& al){ //Assignment Operator
    Order::operator=(al);
    return *this;
}

Airlift::Airlift(const Airlift& al){ //Copy constructor

}

Airlift* Airlift::clone() const 
{
	return new Airlift(*this);
}

bool Airlift::validate(){
    return true;
}

void Airlift::execute(){
    if (validate()) {
        cout << "Airlift: advance some armies from one of the current player's territories to any another territory." << endl;
        notify(this); //Call notify to notify observers
    }
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Negotiate implementation
 * 
 */

Negotiate::Negotiate() : Order("negotiate"){ //Constructor
    _currentState = new string("Negotiate: prevent attacks between the current player and another player until the end of the turn."); //State doesn't change for an order.
}

Negotiate::~Negotiate(){ //Destructor
}

Negotiate& Negotiate::operator=(const Negotiate& ng){ //Assignment Operator
    Order::operator=(ng);
    return *this;
}

Negotiate::Negotiate(const Negotiate& ng){ //Copy constructor

}

Negotiate* Negotiate::clone() const 
{
	return new Negotiate(*this);
}

bool Negotiate::validate(){
    return true;
}

void Negotiate::execute(){
    if (validate()) {
        cout << "Negotiate: prevent attacks between the current player and another player until the end of the turn." << endl;
        notify(this); //Call notify to notify observers
    }
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * OrdersList implementation
 * 
 */

OrdersList::OrdersList() { //Constructor
    _orderlist = new vector <Order*>();
}

OrdersList::~OrdersList() { //Destructor 
    for (int i=0; i < _orderlist->size(); i++) {
		delete(_orderlist->at(i));
	}
	_orderlist->clear();
    delete(_orderlist);
}

OrdersList& OrdersList::operator=(const OrdersList& ol){ //Assignment Operator
    //Wipe out all old orders
    for (int i = 0; i < _orderlist->size(); i++) {
        delete(_orderlist->at(i));
    }
    _orderlist->clear();
    //Clone orders from ol
    for (int i = 0; i < ol._orderlist->size(); i++) {
        this->_orderlist->push_back(ol._orderlist->at(i)->clone()); //Clone all the orders from ol into this list.
    }
    return *this;
}

OrdersList::OrdersList(const OrdersList& ol){ //Copy constructor
    this->_orderlist = new vector<Order*>();
    for (int i = 0; i < ol._orderlist->size(); i++) {
        this->_orderlist->push_back(ol._orderlist->at(i)->clone()); //Clone all the orders from ol into this list.
    }

}

int OrdersList::size(){
	return _orderlist->size();
}

Order* OrdersList::getOrder(int index)
{
	return _orderlist->at(index);
}


void OrdersList::addOrder(Order* order) { 
   this->_orderlist->push_back(order);
}

void OrdersList::move(int from, int to) { 
     swap(_orderlist->at(from),_orderlist->at(to));
}


void OrdersList::remove(int index) { 
    this->_orderlist->erase(this->_orderlist->begin() + index);
}

std::ostream& operator<<(std::ostream& strm, const OrdersList& orderslist)
{
    strm << "OrdersList contents:" << endl;
    for (int i = 0; i < orderslist._orderlist->size(); i++)
        strm << orderslist._orderlist->at(i) << endl;
   
    return strm;
}
