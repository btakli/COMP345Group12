//
// Stub created for A1 Player. NOT REAL CLASS
//

#ifndef BACKUP2022_02_09_ORDER_H
#define BACKUP2022_02_09_ORDER_H


#include <ostream>
using std::string;
using std::ostream;
class Order {
public:
    Order();
    explicit Order(string _name);
    string  _name;
    friend ostream &operator<<(ostream &out, const Order &order);

    string get_order();
};




#endif //BACKUP2022_02_09_ORDER_H
