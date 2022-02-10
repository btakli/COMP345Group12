//
// Stub created for A1 Player. NOT REAL CLASS
//

#ifndef BACKUP2022_02_09_TERRITORY_H
#define BACKUP2022_02_09_TERRITORY_H


#include <string>
using std::string;


class Territory {
public:
    Territory();

    explicit Territory(string name);

    string  _name;
    friend std::ostream &operator<<(std::ostream &out, const Territory &territory);
};


#endif //BACKUP2022_02_09_TERRITORY_H
