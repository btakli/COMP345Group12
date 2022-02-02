#include <iostream>
#include <vector>

using namespace std;

class Order {

public:
    Order();//constructor

    ~Order();//destructor

    Order(Order& o);//copy constructor

    virtual bool validate();

    virtual void execute();

    friend std::ostream& operator<<(std::ostream& description, Order order);//stream insertion operator

};

class Deploy : public Order {

public:
    Deploy();

    ~Deploy();

    Deploy(Deploy& dep);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Deploy deploy);

};

class Advance : public Order{
	
public:
    Advance();

    ~Advance();

    Advance(Advance& adv);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Advance advance);
};

class Bomb : public Order{
	
public:
    Bomb();

    ~Bomb();

    Bomb(Bomb& bmb);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Bomb bomb);

};

class Blockade : public Order{
	
public:
    Blockade();

    ~Blockade();

    Blockade(Blockade& blck);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Blockade blockade);

};

class Airlift : public Order{
	
public:
    Airlift();

    ~Airlift();

    Airlift(Airlift& al);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Airlift airlift);

};

class Negotiate : public Order{
	
public:
    Negotiate(); 

    ~Negotiate();

    Negotiate(Negotiate& ng);

    bool validate();

    void execute();

    friend std::ostream& operator<<(std::ostream& description, Negotiate negotiate);

};

class OrdersList {

    OrdersList();

    ~OrdersList();

    OrdersList(OrdersList& ol);

    void addOrder(Order order);

	void move(int Move, int Location);

	void remove(int Remove);

    friend std::ostream& operator<<(std::ostream& description, OrdersList orderslist);

};
