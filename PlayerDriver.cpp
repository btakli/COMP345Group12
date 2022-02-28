#include <iostream>
#include <vector>
#include "Player.h"
#include "Orders.h"
#include "Map.h"
#include "Cards.h"
using std::string;
using std::vector;
using std::cout;
using std::endl;

int main() {

    cout<< "Demonstration of Player class:" << endl;

    Territory *territory1 = new Territory();
    Territory *territory2 = new Territory();

    vector<Territory *> territories = {territory1, territory2};
    Hand *hand = new Hand();

    OrdersList *listOfOrders= new OrdersList();
    string name = "PlayerName";
    Player  *p = new Player(name, territories, hand, listOfOrders);
    p->issueOrder();
    cout << *p << endl;
    p->toDefend();
    p->toAttack();

    delete(p);
    p = NULL;
    return 0;
}
