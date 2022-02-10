//
// Stub created for A1 Player. NOT REAL CLASS
//

#ifndef BACKUP2022_02_09_HAND_H
#define BACKUP2022_02_09_HAND_H


#include <string>
#include <vector>
using std::string;
using std::vector;
using std::ostream;
class Hand {
public:
    Hand(string name);
    string  _name;
    friend ostream &operator<<(ostream &out, const Hand &hand);
    Hand();

    vector<std::string> _cards;
};


#endif //BACKUP2022_02_09_HAND_H
