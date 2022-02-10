#include <iostream>
#include <vector>
#include "Player.h"
#include "Order.h"
#include "OrdersList.h"
#include "Territory.h"
#include "Hand.h"
using std::string;
using std::vector;
using std::cout;
using std::endl;

int main() {

    cout<< "Demonstration of Player class:" << endl;

    Territory *territory1 = new Territory("t1");
    Territory *territory2 = new Territory("t2");

    vector<Territory *> territories = {territory1, territory2};
    Hand *hand = new Hand("hand");

    OrdersList *listOfOrders= new OrdersList();
    string name = "PlayerName";
    Player  *p = new Player(name, territories, hand, listOfOrders);
    p->issueOrder();
    cout << *p << endl;
    p->toDefend();
    p->toAttack();

    delete(p);
    cout<< "deleted\n"<< *p;
    //cout<< *listOfOrders;
    return 0;
}
