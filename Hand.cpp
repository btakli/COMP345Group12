//
// Stub created for A1 Player. NOT REAL CLASS
//

#include "Hand.h"
using std::string;
using std::vector;
using std::ostream;
Hand::Hand(string name) {
    this->_name = name;
    this->_cards = {"card1", "card2", "card3"};
}

Hand::Hand() {

}

ostream &operator<<(ostream &out, const Hand &hand) {
    out << "Hand name: "+ hand._name + "\n";
    for(const auto& card : hand._cards)
        out<< "\tcard: " +card + "\n";
    return out;
}

