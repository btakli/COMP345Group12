#include "Orders.h"

#include <iostream>
using namespace std;

int main() {

    OrdersList orderslist; //create orders list 

    //create each kind of order and place into the list
    Order* o1 = new Deploy();
    Order* o2 = new Advance();
    Order* o3 = new Bomb();
    Order* o4 = new Blockade();
    Order* o5 = new Airlift();
    Order* o6 = new Negotiate();

    orderslist.addOrder(o1);
    orderslist.addOrder(o2);
    orderslist.addOrder(o3);
    orderslist.addOrder(o4);
    orderslist.addOrder(o5);
    orderslist.addOrder(o6);
	
    delete(o1);
    delete(o2);
    delete(o3);
    delete(o4);
    delete(o5);
    delete(o6);
    
    o1 = NULL;
    o2 = NULL;
    o3 = NULL;
    o4 = NULL;
    o5 = NULL;
    o6 = NULL;

};
