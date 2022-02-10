//
// Stub created for A1 Player. NOT REAL CLASS
//

#include "Territory.h"
using std::string;

Territory::Territory(std::string name) {
    this->_name = name;
}

Territory::Territory() {

}

std::ostream &operator<<(std::ostream &out, const Territory &territory) {
    out << "Territory: " + territory._name;
    return out;
}
