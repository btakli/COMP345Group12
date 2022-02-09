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

    virtual Order& operator=(const Order& o);//assignment operator

    virtual Order* clone() const;//clone function

    virtual bool validate();

    virtual void execute();

private:
    friend std::ostream& operator<<(std::ostream& description, Order order);//stream insertion operator

};

class Deploy : public Order {

public:
    Deploy();

    virtual ~Deploy();

    Deploy(const Deploy& dep);

    virtual Deploy& operator=(const Deploy& dep);

    virtual Deploy* clone() const;

    bool validate();

    void execute();

private:
    friend std::ostream& operator<<(std::ostream& description, Deploy deploy);

};

class Advance : public Order{
	
public:
    Advance();

    virtual ~Advance();

    Advance(const Advance& adv);

    virtual Advance& operator=(const Advance& adv);

    virtual Advance* clone() const;

    bool validate();

    void execute();

  private:  
    friend std::ostream& operator<<(std::ostream& description, Advance advance);
};

class Bomb : public Order{
	
public:
    Bomb();

    virtual ~Bomb();

    Bomb(const Bomb& bmb);

    virtual Bomb& operator=(const Bomb& bmb);

    virtual Bomb* clone() const;

    bool validate();

    void execute();

private:
    friend std::ostream& operator<<(std::ostream& description, Bomb bomb);

};

class Blockade : public Order{
	
public:
    Blockade();

    virtual ~Blockade();

    Blockade(const Blockade& blck);

    virtual Blockade& operator=(const Blockade& blck);

    virtual Blockade* clone() const;

    bool validate();

    void execute();

private:
    friend std::ostream& operator<<(std::ostream& description, Blockade blockade);

};

class Airlift : public Order{
	
public:
    Airlift();

    virtual ~Airlift();

    Airlift(const Airlift& al);

    virtual Airlift& operator=(const Airlift& al);

    virtual Airlift* clone() const;

    bool validate();

    void execute();

private:
    friend std::ostream& operator<<(std::ostream& description, Airlift airlift);

};

class Negotiate : public Order{
	
public:
    Negotiate();

    virtual ~Negotiate();

    Negotiate(const Negotiate& ng);

    virtual Negotiate& operator=(const Negotiate& ng);

    virtual Negotiate* clone() const;

    bool validate();

    void execute();

private:
    friend std::ostream& operator<<(std::ostream& description, Negotiate negotiate);

};

class OrdersList {

public:
    OrdersList();

    ~OrdersList();

    OrdersList(const OrdersList& ol);

    OrdersList& operator=(const OrdersList& ol);

    std::vector<Order*> getOrdersList();

    void addOrder(Order* order); 

    void move(int From, int To);

    void remove(int Index);

private:
    std::vector<Order*>* _orderlist;

    friend std::ostream& operator<<(std::ostream& description, OrdersList orderslist);

};
