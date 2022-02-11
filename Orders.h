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

    Order(std::string type);

    std::string getType() const;

    virtual Order& operator=(const Order& o);//assignment operator

    virtual Order* clone() const;//clone function

    virtual bool validate();

    virtual void execute();

private:
    friend std::ostream& operator<<(std::ostream& description, const Order& order);//stream insertion operator

    std::string* _type;
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
    friend std::ostream& operator<<(std::ostream& description, const Deploy& deploy);

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
    friend std::ostream& operator<<(std::ostream& description, const Advance& advance);
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
    friend std::ostream& operator<<(std::ostream& description, const Bomb& bomb);

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
    friend std::ostream& operator<<(std::ostream& description, const Blockade& blockade);

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
    friend std::ostream& operator<<(std::ostream& description, const Airlift& airlift);

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
    friend std::ostream& operator<<(std::ostream& description, const Negotiate& negotiate);

};

class OrdersList {

public:
    OrdersList();

    ~OrdersList();

    OrdersList(const OrdersList& ol);

    OrdersList& operator=(const OrdersList& ol);

    std::vector<Order*> getOrdersList();

    int size();

    Order* getOrders(int index);

    void addOrder(Order* order); 

    void move(int from, int to);

    void remove(int index);

private:
    std::vector<Order*>* _orderlist;

    friend std::ostream& operator<<(std::ostream& description, const OrdersList& orderslist);

};
