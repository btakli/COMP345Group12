#include "Orders.h"
#include <vector>
#include <iostream>
#include "Map.h"
#include "GameEngine.h"
#include "Player.h"
#include "Cards.h"
#include <cmath>

using namespace std;

//GameEngine *Order::game = new GameEngine();

/**
 * Order implementation
 * 
 */

Order::Order() : _type(new string("Default Order")){
    _currentState->assign("Order: Default Order");
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
   _currentState->assign("Deploy: place some armies on one of the current player's territories.");

    player = nullptr;
    targetTerritory = nullptr;
    armiesToDeploy = 0;
}



Deploy::Deploy(Player* p, Territory* target, int numToDeploy) : Deploy() {
    player = p;
    this->targetTerritory = target;
    armiesToDeploy = numToDeploy;
}

Deploy::~Deploy(){ //Destructor
}

Deploy& Deploy::operator=(const Deploy& dep){ //Assignment Operator
    Order::operator=(dep);
    return *this;
}

Deploy::Deploy(const Deploy& dep){ //Copy constructor
    this->_currentState->assign(*dep._currentState);
    this->player = dep.player;
    this->targetTerritory = dep.targetTerritory;
    this->armiesToDeploy = dep.armiesToDeploy;
}

Deploy* Deploy::clone() const 
{
	return new Deploy(*this);
}

bool Deploy::validate(){
    //New Implementation
     // Check if territory belongs to player
    if (targetTerritory->get_claimant() == nullptr) return false;

    if (targetTerritory->get_claimant() == player){
        cout << "valid order" << endl;
        return true;
    }else{
        cout << "invalid order" << endl;
        return false;
    }
}

void Deploy::execute(){
    if (validate()) {
        //cout << "Deploy: place some armies on one of the current player's territories." << endl;
        //New Implementation
        targetTerritory->set_stationed_army(*new int(targetTerritory->get_stationed_army() + armiesToDeploy));
        _currentState->append("\n\t" + *player->getName() + " deploying on territory " + targetTerritory->get_name() + " " + std::to_string(armiesToDeploy) + " armies.");
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
    _currentState->assign("Advance: move some armies from one of the current player's territories (source) to an adjacent territory (target).");
    player = nullptr;
    sourceTerritory = nullptr;
    targetTerritory = nullptr;
    armiesToAdvance = 0;
}

Advance::Advance(Player* p, Territory* source, Territory* target) : Advance() {
    player = p;
    this->sourceTerritory = source;
    this->targetTerritory = target;
}

Advance::~Advance(){ //Destructor
}

Advance& Advance::operator=(const Advance& adv){ //Assignment Operator
    Order::operator=(adv);
    return *this;
}

Advance::Advance(const Advance& adv) { //Copy constructor
    this->_currentState->assign(*adv._currentState);
    this->player = adv.player;
    this->sourceTerritory = adv.sourceTerritory;
    this->targetTerritory = adv.targetTerritory;
    this->armiesToAdvance = adv.armiesToAdvance;
}

Advance* Advance::clone() const 
{
	return new Advance(*this);
}

//Check if 2 Territories are adjacent
bool Advance::validate(){
    
    for (Territory* ter : targetTerritory->get_neighbors()) 
        if (sourceTerritory == ter) 
            return true;

    return false;
}


void Advance::execute() {

    if (!validate()) {
        cout << "INVALID ORDER" << endl;
        return;
    }


    cout << "Advance: move some armies from one of the current player's territories (source) to an adjacent territory (target)." << endl;

    if (targetTerritory->get_claimant() == player) { //advance 
        cout << "Reinforce" << endl;
        targetTerritory->set_stationed_army(targetTerritory->get_stationed_army() + sourceTerritory->get_stationed_army());
        sourceTerritory->set_stationed_army(0);

        _currentState->append("\n\t" + *player->getName() + " moving " + std::to_string(sourceTerritory->get_stationed_army()) + " armies from "
            + sourceTerritory->get_name() + " to their other territory " + targetTerritory->get_name());
    }
    else if (targetTerritory->get_claimant() != player) { //attack
        cout << "Attacking" << endl;
        _currentState->append("\n\t" + *player->getName() + " attacking with " + std::to_string(sourceTerritory->get_stationed_army()) + " armies from "
            + sourceTerritory->get_name() + " the enemy territory " + targetTerritory->get_name());
        
        targetTerritory->get_claimant()->setWasAttacked(true);

        float attackingChances = sourceTerritory->get_stationed_army() * 0.6;
        float defendingChances = targetTerritory->get_stationed_army() * 0.7;

        if (attackingChances == defendingChances) {
            int sourceArmy = sourceTerritory->get_stationed_army();
            int targetArmy = targetTerritory->get_stationed_army();

            targetTerritory->set_stationed_army(abs(sourceArmy - targetArmy));
            sourceTerritory->set_stationed_army(abs(sourceArmy - targetArmy));
        }
        else if (attackingChances > defendingChances) {
            targetTerritory->set_stationed_army((attackingChances - defendingChances) / 0.6);
            sourceTerritory->set_stationed_army(0);

            auto it= targetTerritory->get_claimant()->get_territories().begin();

            for (Territory* t : targetTerritory->get_claimant()->get_territories()) {
                if (t == targetTerritory) 
                    break;
                advance(it, 1);
            }
            if (it != targetTerritory->get_claimant()->get_territories().end())
                targetTerritory->get_claimant()->get_territories().erase(it);

            targetTerritory->claim(player, false);
            player->get_territories().push_back(targetTerritory);

            player->drawCard();
        }
    }
    notify(this); //Call notify to notify observers
    
}

/**
 * Bomb implementation
 * 
 */

Bomb::Bomb() : Order("bomb"){ //Constructor
    _currentState->assign("Bomb: destroy half of the armies located on an opponent???s territory that is adjacent to one of the current player's territories.");
    targetTerritory = nullptr;
}

Bomb::Bomb(Territory* target) : Bomb() {

    this->targetTerritory = target;
}

Bomb::~Bomb(){ //Destructor
}

Bomb& Bomb::operator=(const Bomb& bmb){ //Assignment Operator
    Order::operator=(bmb);
    return *this;
}

Bomb::Bomb(const Bomb& bmb){ //Copy constructor
    this->_currentState->assign(*bmb._currentState);
    this->targetTerritory = bmb.targetTerritory;
}

Bomb* Bomb::clone() const 
{
	return new Bomb(*this);
}

bool Bomb::validate(){
    //New Implementation
    for (Territory* ter: targetTerritory->get_neighbors()){
        if(targetTerritory != ter){ //Check if 2 Territories are adjacent
               cout << "invalid order, the territories are not adjacent"<< endl;
               return false;
        }else if(targetTerritory->get_claimant() != nullptr){ // Check if territory belongs to player
            cout << "invalid order, don't own territory" << endl;
            return false;
        }else{
            return true;
        }
}
}

void Bomb::execute(){
    
    cout << "Bomb: destroy half of the armies located on an opponent???s territory that is adjacent to one of the current player's territories." << endl;
    int bombedArmies = (targetTerritory->get_stationed_army()) / 2;
    targetTerritory->set_stationed_army(bombedArmies);
    _currentState->append("\n\t" + targetTerritory->get_name() + " was bombed!");
    notify(this); //Call notify to notify observers
}

/**
 * Blockade implementation
 * 
 */

Blockade::Blockade() : Order("blockade"){ //Constructor
   _currentState->assign("Blockade: triple the number of armies on one of the current player's territories and make it a neutral territory.");
   targetTerritory = nullptr;
}

Blockade::Blockade(Territory* target) : Blockade() {
    this->targetTerritory = target;
}

Blockade::~Blockade(){ //Destructor
}

Blockade& Blockade::operator=(const Blockade& blck){ //Assignment Operator
    Order::operator=(blck);
    return *this;
}

Blockade::Blockade(const Blockade& blck){ //Copy constructor
    this->_currentState->assign(*blck._currentState);
    this->targetTerritory = blck.targetTerritory;
}

Blockade* Blockade::clone() const 
{
	return new Blockade(*this);
}

bool Blockade::validate(){
   //New Implementation
    // Check if territory belongs to player
    if (targetTerritory->get_claimant() == nullptr) {
        cout << "valid order, owned territory" << endl;
        return true;
    }else
    return false;
}

void Blockade::execute(){
    //cout << "Blockade: triple the number of armies on one of the current player's territories and make it a neutral territory." << endl;
    int doubleArmies = (targetTerritory->get_stationed_army()) * 2;
    targetTerritory->set_stationed_army(doubleArmies);
    targetTerritory->claim(nullptr, false);
    _currentState->append("\n\tDoubled army count on " + targetTerritory->get_name() + " to " + std::to_string(doubleArmies) + " armies");
    notify(this); //Call notify to notify observers
}


/**
 * Airlift implementation
 * 
 */

Airlift::Airlift() : Order("airlift"){ //Constructor
   _currentState = new string("Airlift: advance some armies from one of the current player's territories to any another territory.");
   sourceTerritory = nullptr;
   targetTerritory = nullptr;
   armiesToAirlift = 0;
}

Airlift::Airlift(Territory* source, Territory* target) : Airlift() {
    this->sourceTerritory = source;
    this->targetTerritory = target;
}


Airlift::~Airlift(){ //Destructor
}

Airlift& Airlift::operator=(const Airlift& al){ //Assignment Operator
    Order::operator=(al);
    return *this;
}

Airlift::Airlift(const Airlift& al){ //Copy constructor
    this->_currentState->assign(*al._currentState);
    this->sourceTerritory = al.sourceTerritory;
    this->targetTerritory = al.targetTerritory;
    this->armiesToAirlift = al.armiesToAirlift;
}

Airlift* Airlift::clone() const 
{
	return new Airlift(*this);
}

bool Airlift::validate(){
    //New Implementation
    //Check if both territories belong to player
    if (targetTerritory->get_claimant() == sourceTerritory->get_claimant()){
        cout << "valid order" << endl;
        return true;
    } else {
        cout << "invalid order, don't own both territories" << endl;
        return false;
    }
}

void Airlift::execute(){
    if (validate()) {
        cout << "Airlift: advance some armies from one of the current player's territories to any another territory." << endl;
        //new implementation
        targetTerritory->set_stationed_army(targetTerritory->get_stationed_army() + sourceTerritory->get_stationed_army());
        sourceTerritory->set_stationed_army(0);
        _currentState->append("\n\tAdvancing armies from " + sourceTerritory->get_name() + " to " + targetTerritory->get_name());
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
    _currentState->assign("Negotiate: prevent attacks between the current player and another player until the end of the turn.");
    player = nullptr;
    targetPlayer = nullptr;
}

Negotiate::Negotiate(Player* p, Player* target) : Negotiate() {
    player = p;
    targetPlayer = target;
}


Negotiate::~Negotiate(){ //Destructor
}

Negotiate& Negotiate::operator=(const Negotiate& ng){ //Assignment Operator
    Order::operator=(ng);
    return *this;
}

Negotiate::Negotiate(const Negotiate& ng){ //Copy constructor
    _currentState->assign(*ng._currentState);
    player = ng.player;
    targetPlayer = ng.targetPlayer;
}

Negotiate* Negotiate::clone() const 
{
	return new Negotiate(*this);
}

bool Negotiate::validate(){
    //New Implementation
    //Check if the player issuing the negotiation is the same as the target player
    if (player == targetPlayer) {
        return false;
        cout << "invalid order : negotiation must be done with a different player\n";
    } else
        return true;
}

void Negotiate::execute(){
    if (validate()) {
        cout << "Negotiate: prevent attacks between the current player and another player until the end of the turn." << endl;
        _currentState->append("\n\tPreventing attacks between " + *player->getName() + " and " + *targetPlayer->getName());
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
    _orderlist = new queue<Order*>();
    _currentState = new string("NO ORDERS CURRENTLY");
}

OrdersList::~OrdersList() { //Destructor 

    delete _orderlist;
}

OrdersList& OrdersList::operator=(const OrdersList& ol){ //Assignment Operator
    //Wipe out all old orders
    for (int i = 0; i < _orderlist->size(); i++) {
        _orderlist->pop();
    }

    //Clone orders from ol
    for (int i = 0; i < ol._orderlist->size(); i++) {

        Order* o = ol._orderlist->front();
        ol._orderlist->pop();
        ol._orderlist->push(o);
        this->_orderlist->push(o); //Clone all the orders from ol into this list.
    }
    return *this;
}

OrdersList::OrdersList(const OrdersList& ol){ //Copy constructor
    this->_orderlist = new queue<Order*>();

    //Clone orders from ol
    for (int i = 0; i < ol._orderlist->size(); i++) {

        Order* o = ol._orderlist->front();
        ol._orderlist->pop();
        ol._orderlist->push(o);
        this->_orderlist->push(o); //Clone all the orders from ol into this list.
    }
    _currentState->assign(*ol._currentState); // NOT SURE IF THIS IS SUPPOSE TO BE HERE - YU

    _currentState = new string(*ol._currentState);
}

int OrdersList::size(){
	return _orderlist->size();
}

void OrdersList::addOrder(Order* order) { 
    _currentState->assign(order->getType());
    this->_orderlist->push(order);
    notify(this);
}

void OrdersList::remove() { 
    _orderlist->pop();
}

void OrdersList::clearOrders()
{
    while (!_orderlist->empty())
        _orderlist->pop();
}

std::string OrdersList::stringToLog()
{
    return "Order Issued: " + *_currentState;
}

std::queue<Order*>& OrdersList::get_order_list()
{
    return *this->_orderlist;
}

std::ostream& operator<<(std::ostream& strm, const OrdersList& orderslist)
{
    strm << "OrdersList contents: " << endl;

    for (int i = 0; i < orderslist._orderlist->size(); i++) {

        Order* o = orderslist._orderlist->front();
        strm << *o << endl;
        orderslist._orderlist->pop();
        orderslist._orderlist->push(o);
    }
   
    return strm;
}
