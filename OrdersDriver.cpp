#include "Orders.h"

#include <iostream>
using namespace std;

int main() {

    OrdersList orderslist; //create orders list 

    //creeate each kind of order and place into the list
    orderslist.addOrder(new Deploy());
    orderslist.addOrder(new Advance());
    orderslist.addOrder(new Bomb());
    orderslist.addOrder(new Blockade());
    orderslist.addOrder(new Airlift());
	  orderslist.addOrder(new Negotiate());

};
