#include "Orders.h"
#include <vector>
#include <iostream>
using namespace std;


/**
 * Order implementation
 * 
 */

Order::Order() : _type(new string("Default Order")){
    
}

Order::Order(string type)
{
	this->_type = new string(type);
}

string Order::getType() const
{
	return *(_type);
}

Order::~Order(){ //Desctructor
    delete(_type);
}

Order& Order::operator=(const Order& o){ //Assignment Operator
    this->_type = new string(*(o._type));
	return *this;
}

Order::Order(const Order& o){ //Copy constructor

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
  if(validate())
      cout << "" << endl;
   else
      cout << "INVALID ORDER" << endl;

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

}

Deploy::~Deploy(){ //Desctructor
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
  if(validate())
      cout << "Deploy: place some armies on one of the current player’s territories." << endl;
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Advance implementation
 * 
 */

Advance::Advance() : Order("advance"){ //Constructor

}

Advance::~Advance(){ //Desctructor
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
  if(validate())
      cout << "Advance: move some armies from one of the current player’s territories (source) to an adjacent territory (target)." << endl;
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Bomb implementation
 * 
 */

Bomb::Bomb() : Order("bomb"){ //Constructor

}

Bomb::~Bomb(){ //Desctructor
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
  if(validate())
      cout << "Bomb: destroy half of the armies located on an opponent’s territory that is adjacent to one of the current player’s territories." << endl;
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Blockade implementation
 * 
 */

Blockade::Blockade() : Order("blockade"){ //Constructor

}

Blockade::~Blockade(){ //Desctructor
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
  if(validate())
      cout << "Blockade: triple the number of armies on one of the current player’s territories and make it a neutral territory." << endl;
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Airlift implementation
 * 
 */

Airlift::Airlift() : Order("airlift"){ //Constructor

}

Airlift::~Airlift(){ //Desctructor
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
  if(validate())
      cout << "Airlift: advance some armies from one of the current player’s territories to any another territory." << endl;
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * Negotiate implementation
 * 
 */

Negotiate::Negotiate() : Order("negotiate"){ //Constructor

}

Negotiate::~Negotiate(){ //Desctructor
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
  if(validate())
      cout << "Negotiate: prevent attacks between the current player and another player until the end of the turn." << endl;
   else
      cout << "INVALID ORDER" << endl;

}

/**
 * OrdersList implementation
 * 
 */

OrdersList::OrdersList() { //Constructor

}

OrdersList::~OrdersList() { //Desctructor
	for (Order* order : *_orderlist) {
		delete order;
		order = nullptr;
	}
	this->_orderlist->clear();
}

OrdersList& OrdersList::operator=(const OrdersList& ol){ //Assignment Operator
    OrdersList::operator=(ol);
    return *this;
}

OrdersList::OrdersList(const OrdersList& ol){ //Copy constructor

}

int OrdersList::size()
{
	return _orderlist->size();
}

Order* OrdersList::getOrders(int index)
{
	return _orderlist->at(index);
}

void OrdersList::addOrder(Order* order) {
   this->_orderlist->push_back(order);
}

void OrdersList::move(int from, int to) {
    swap(this->_orderlist[from],this->_orderlist[to]);
}

void OrdersList::remove(int index) {
    this->_orderlist->erase(this->_orderlist->begin() + index);
}



