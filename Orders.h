#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "LoggingObserver.h"

using namespace std;

//Base class for all orders
class Order : public ILoggable, public Subject {

public:
    //default constructor
    Order();
    //destructor
    virtual ~Order();
    //copy constructor
    Order(const Order& o);
    //constructor taking in a string setting the type of the order
    Order(std::string type);
    //get the order type as a string
    std::string getType() const;
    //assignment operator
    virtual Order& operator=(const Order& o);
    //clone function
    virtual Order* clone() const;
    //validate method to make sure an order is of a valid type
    virtual bool validate();
    //execute method to execute the action of the order and display its description
    virtual void execute();
    //Method responsible for writing a specific string based on the type of order. Abstract method from ILoggable.
    std::string stringToLog();

private:
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& description, const Order& order);
    //order type
    std::string* _type;
};

class Deploy : public Order {

public:
    //default constructor
    Deploy();
    //destructor
    virtual ~Deploy();
    //copy constructor
    Deploy(const Deploy& dep);
    //assignment operator
    virtual Deploy& operator=(const Deploy& dep);
    //clone function
    virtual Deploy* clone() const;
    //validate method to make sure an order is of a valid type
    bool validate();
    //execute method to execute the action of the order and display its description
    void execute();

private:
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& description, const Deploy& deploy);

};

class Advance : public Order{
	
public:
    //default constructor
    Advance();
    //destructor
    virtual ~Advance();
    //copy constructor
    Advance(const Advance& adv);
    //assignment operator
    virtual Advance& operator=(const Advance& adv);
    //clone function
    virtual Advance* clone() const;
    //validate method to make sure an order is of a valid type
    bool validate();
    //execute method to execute the action of the order and display its description
    void execute();

  private:
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& description, const Advance& advance);
};

class Bomb : public Order{
	
public:
    //default constructor
    Bomb();
    //destructor
    virtual ~Bomb();
    //copy constructor
    Bomb(const Bomb& bmb);
    //assignment operator
    virtual Bomb& operator=(const Bomb& bmb);
    //clone function
    virtual Bomb* clone() const;
    //validate method to make sure an order is of a valid type
    bool validate();
    //execute method to execute the action of the order and display its description
    void execute();

private:
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& description, const Bomb& bomb);

};

class Blockade : public Order{
	
public:
    //default constructor
    Blockade();
    //destructor
    virtual ~Blockade();
    //copy constructor
    Blockade(const Blockade& blck);
    //assignment operator
    virtual Blockade& operator=(const Blockade& blck);
    //clone function
    virtual Blockade* clone() const;
    //validate method to make sure an order is of a valid type
    bool validate();
    //execute method to execute the action of the order and display its description
    void execute();

private:
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& description, const Blockade& blockade);

};

class Airlift : public Order{
	
public:
    //default constructor
    Airlift();
    //destructor
    virtual ~Airlift();
    //copy constructor
    Airlift(const Airlift& al);
    //assignment operator
    virtual Airlift& operator=(const Airlift& al);
    //clone function
    virtual Airlift* clone() const;
    //validate method to make sure an order is of a valid type
    bool validate();
    //execute method to execute the action of the order and display its description
    void execute();

private:
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& description, const Airlift& airlift);
};

class Negotiate : public Order{
	
public:
    //default constructor
    Negotiate();
    //destructor
    virtual ~Negotiate();
    //copy constructor
    Negotiate(const Negotiate& ng);
    //assignment operator
    virtual Negotiate& operator=(const Negotiate& ng);
    //clone function
    virtual Negotiate* clone() const;
    //validate method to make sure an order is of a valid type
    bool validate();
    //execute method to execute the action of the order and display its description
    void execute();

private:
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& description, const Negotiate& negotiate);

};

class OrdersList : public ILoggable, public Subject {

public:
    //default constructor
    OrdersList();
    //destructor
    ~OrdersList();
    //copy constructor
    OrdersList(const OrdersList& ol);
    //assignment operator
    OrdersList& operator=(const OrdersList& ol);
    //return the size of the orderslist
    int size();
    //get an order at a specific index
	Order* getOrder(int index);
    //addOrder method to add all kind of orders in the orderslist
    void addOrder(Order* order);
    //move method to move orders inside the list, takes two ints as input and swaps the orders at these indices
	void move(int from, int to);
    //remove method to delete a specific order from the list using its index inside the orderslist
	void remove(int index);
    //Method responsible for writing a specific string based on the type of order added to the list. Abstract method from ILoggable.
    std::string stringToLog();

private:
    //The vector of Order pointers
    std::vector<Order*>* _orderlist;
    //stream insertion operator
    friend std::ostream& operator<<(std::ostream& strm, const OrdersList& orderslist);

};
