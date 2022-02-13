#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Base class for all orders
class Order {

public:
    Order();//default constructor

    virtual ~Order();//destructor

    Order(const Order& o);//copy constructor

    Order(std::string type);//constructor taking in a string setting the type of the order

    std::string getType() const;//get the order type as a string

    virtual Order& operator=(const Order& o);//assignment operator

    virtual Order* clone() const;//clone function

    virtual bool validate();//validate method to make sure an order is of a valid type

    virtual void execute();//execute method to execute the action of the order and display its description

private:
    friend std::ostream& operator<<(std::ostream& description, const Order& order);//stream insertion operator

    std::string* _type;//order type
};

class Deploy : public Order {

public:
    Deploy();//default constructor

    virtual ~Deploy();//destructor

    Deploy(const Deploy& dep);//copy constructor

    virtual Deploy& operator=(const Deploy& dep);//assignment operator

    virtual Deploy* clone() const;//clone function

    bool validate();//validate method to make sure an order is of a valid type

    void execute();//execute method to execute the action of the order and display its description

private:
    friend std::ostream& operator<<(std::ostream& description, const Deploy& deploy);//stream insertion operator

};

class Advance : public Order{
	
public:
    Advance();//default constructor

    virtual ~Advance();//destructor

    Advance(const Advance& adv);//copy constructor

    virtual Advance& operator=(const Advance& adv);//assignment operator

    virtual Advance* clone() const;//clone function

    bool validate();//validate method to make sure an order is of a valid type

    void execute();//execute method to execute the action of the order and display its description

  private:  
    friend std::ostream& operator<<(std::ostream& description, const Advance& advance);//stream insertion operator
};

class Bomb : public Order{
	
public:
    Bomb();//default constructor

    virtual ~Bomb();//destructor

    Bomb(const Bomb& bmb);//copy constructor

    virtual Bomb& operator=(const Bomb& bmb);//assignment operator

    virtual Bomb* clone() const;//clone function

    bool validate();//validate method to make sure an order is of a valid type

    void execute();//execute method to execute the action of the order and display its description

private:
    friend std::ostream& operator<<(std::ostream& description, const Bomb& bomb);//stream insertion operator

};

class Blockade : public Order{
	
public:
    Blockade();//default constructor

    virtual ~Blockade();//destructor

    Blockade(const Blockade& blck);//copy constructor

    virtual Blockade& operator=(const Blockade& blck);//assignment operator

    virtual Blockade* clone() const;//clone function

    bool validate();//validate method to make sure an order is of a valid type

    void execute();//execute method to execute the action of the order and display its description

private:
    friend std::ostream& operator<<(std::ostream& description, const Blockade& blockade);//stream insertion operator

};

class Airlift : public Order{
	
public:
    Airlift();//default constructor

    virtual ~Airlift();//destructor

    Airlift(const Airlift& al);//copy constructor

    virtual Airlift& operator=(const Airlift& al);//assignment operator

    virtual Airlift* clone() const;//clone function

    bool validate();//validate method to make sure an order is of a valid type

    void execute();//execute method to execute the action of the order and display its description

private:
    friend std::ostream& operator<<(std::ostream& description, const Airlift& airlift);//stream insertion operator

};

class Negotiate : public Order{
	
public:
    Negotiate();//default constructor

    virtual ~Negotiate();//destructor

    Negotiate(const Negotiate& ng);//copy constructor

    virtual Negotiate& operator=(const Negotiate& ng);//assignment operator

    virtual Negotiate* clone() const;//clone function

    bool validate();//validate method to make sure an order is of a valid type

    void execute();//execute method to execute the action of the order and display its description

private:
    friend std::ostream& operator<<(std::ostream& description, const Negotiate& negotiate);//stream insertion operator

};

class OrdersList {

public:
    OrdersList();//default constructor

    ~OrdersList();//destructor

    OrdersList(const OrdersList& ol);//copy constructor

    OrdersList& operator=(const OrdersList& ol);//assignment operator

    int size();//return the size of the orderslist

	Order* getOrder(int index);//get an order at a specific index

    void addOrder(Order* order);//addOrder method to add all kind of orders in the orderslist

	void move(int from, int to);//move method to move orders inside the list, takes two ints as input and swaps the orders at these indices

	void remove(int index);//remove method to delete a specific order from the list using its index inside the orderslist

private:
    std::vector<Order*>* _orderlist;
     
    friend std::ostream& operator<<(std::ostream& description, const OrdersList& orderslist);//stream insertion operator

};
