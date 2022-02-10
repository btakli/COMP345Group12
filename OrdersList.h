//
// Created by booty on 2022-02-09.
//

#ifndef BACKUP2022_02_09_ORDERSLIST_H
#define BACKUP2022_02_09_ORDERSLIST_H


#include <string>
#include <vector>
#include "Order.h"
using std::string;
using std::vector;
using std::ostream;
class OrdersList {
public:
    OrdersList();


    string  _name;
    friend ostream &operator<<(ostream &out, const OrdersList &ordersList);

    void addOrder(Order *pOrder);

    vector<Order> _listOfOrders;
};


#endif //BACKUP2022_02_09_ORDERSLIST_H
