#include "Orders.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;
using namespace std;

int main() {

    //Create a new OrdersList
    OrdersList* orderslist = new OrdersList();

    //Create the different kinds of orders
    Order* o1 = new Order();
    Order* o2 = new Deploy();
    Order* o3 = new Advance();
    Order* o4 = new Bomb();
    Order* o5 = new Blockade();
    Order* o6 = new Airlift();
    Order* o7 = new Negotiate();

    //Put the orders in the first OrdersList using the addOrder() method
    orderslist->addOrder(o1);
    orderslist->addOrder(o2);
    orderslist->addOrder(o3);
    orderslist->addOrder(o4);
    orderslist->addOrder(o5);
    orderslist->addOrder(o6);
    orderslist->addOrder(o7);


    //print the OrdersList
    cout<<"Orders in the list:"<< endl;
    for (int i=0; i < orderslist->size(); i++) {
        cout <<*orderslist->getOrder(i)<< endl;
    }
    cout <<"\n"<< endl;
    
    //executing valid orders
    cout <<"Executing orders if they are valid:"<< endl;
    o1->execute(); //invalid order
    o2->execute(); //valid order, prints its description.
    cout <<"\n"<< endl;

    //moving orders inside the list 
    cout << "Before moving the orders in the list:" <<endl;
    for (int i=0; i < orderslist->size(); i++) {
       cout <<*orderslist->getOrder(i)<< endl;
    }
    orderslist->move(2,3);
    cout <<"\n"<< endl;
    cout << "After moving the orders in the list:" <<endl;
    for (int i=0; i < orderslist->size(); i++) {
       cout <<*orderslist->getOrder(i)<< endl;
    }

   // removing an order from the list
   cout <<"\n"<< endl;
    cout << "List before removing order at index 3 in the list:" <<endl;
	for (int i=0; i < orderslist->size(); i++) {
        cout <<*orderslist->getOrder(i)<< endl;
    }
	orderslist->remove(3);
    cout <<"\n"<< endl;
	cout << "List after removing the order:" <<endl;
	for (int i=0; i < orderslist->size(); i++) {
        cout <<*orderslist->getOrder(i)<< endl;
    }


    //Delete everything
    delete orderslist;
    o1 = NULL;
    o2 = NULL;
    o3 = NULL;
    o4 = NULL;
    o5 = NULL;
    o6 = NULL;
    o7 = NULL;
    orderslist = NULL;
    return 0;
}
