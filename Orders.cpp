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

Order::~Order(){ //Desctructor
}

Order& Order::operator=(const Order& o){ //Assignment Operator

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

std::ostream& operator<<(std::ostream& strm, const Order& o)
{
	return strm << "Order of Type: " << o.getType();
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
      cout << "Deploy" << endl;
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
      cout << "Advance" << endl;
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
      cout << "Bomb" << endl;
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
      cout << "Blockade" << endl;
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
      cout << "Airlift" << endl;
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
      cout << "Negotiate" << endl;
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
}

OrdersList& OrdersList::operator=(const OrdersList& ol){ //Assignment Operator

}

OrdersList::OrdersList(const OrdersList& ol){ //Copy constructor

}

void OrdersList::addOrder(Order* order) {
    _orderlist->push_back(order);
	
}

void OrdersList::move(int From, int To) {
    
}

void OrdersList::remove(int Index) {
   

}



