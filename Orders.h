#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Order {

public:
    Order();

    ~Order();

    Order(const Order& o);

    Order& operator=(const Order& o);

    virtual bool validate();

    virtual void execute();

    friend std::ostream& operator<<(std::ostream& description, Order order);//stream insertion operator

};

class Deploy : public Order {

public:
    Deploy();

    ~Deploy();

    Deploy(const Deploy& dep);

    Deploy& operator=(const Deploy& dep);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Deploy deploy);

};

class Advance : public Order{
	
public:
    Advance();

    ~Advance();

    Advance(const Advance& adv);

    Advance& operator=(const Advance& adv);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Advance advance);
};

class Bomb : public Order{
	
public:
    Bomb();

    ~Bomb();

    Bomb(const Bomb& bmb);

    Bomb& operator=(const Bomb& bmb);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Bomb bomb);

};

class Blockade : public Order{
	
public:
    Blockade();

    ~Blockade();

    Blockade(const Blockade& blck);

    Blockade& operator=(const Blockade& blck);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Blockade blockade);

};

class Airlift : public Order{
	
public:
    Airlift();

    ~Airlift();

    Airlift(const Airlift& al);

    Airlift& operator=(const Airlift& al);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Airlift airlift);

};

class Negotiate : public Order{
	
public:
    Negotiate();

    ~Negotiate();

    Negotiate(const Negotiate& ng);

    Negotiate& operator=(const Negotiate& ng);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Negotiate negotiate);

};

class OrdersList {

    OrdersList();

    ~OrdersList();

    OrdersList(const OrdersList& ol);

    OrdersList& operator=(const OrdersList& ol);

    //void addOrder(Order order); put addOrder method?

	void move(int Move, int Location);

	void remove(int Remove);

    friend std::ostream& operator<<(std::ostream& description, OrdersList orderslist);

};
