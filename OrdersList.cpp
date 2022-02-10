//
// Stub created for A1 Player. NOT REAL CLASS
//
#include "OrdersList.h"
#include <string>
using std::string;
using std::vector;

OrdersList::OrdersList() {
    Order order1("order1");
    Order order2("order2");
    Order order3("order3");
    Order order4("order4");

    _listOfOrders = {order1, order2, order3, order4};
}

void OrdersList::addOrder(Order *pOrder) {
    this->_listOfOrders.push_back(*pOrder);
}



ostream &operator<<(ostream &out, const OrdersList &orderList) {
    out << "List of orders: \n";
    for(Order order : orderList._listOfOrders)
        out<< "\tOrder: " +   order.get_order() + "\n";
    return out;
}


