//
// Stub created for A1 Player. NOT REAL CLASS
//
#include <iostream>
#include "Order.h"

std::ostream &operator<<(std::ostream &out, const Order &order) {
    out << "Player: " + order._name;
    return out;
}

Order::Order() {

}

Order::Order(std::string _name) {
    this->_name = _name;
}

std::string Order::get_order() {
    std::string out = this->_name;
    return out;
}
