//
// Created by crvlh8 on 3/21/24.
//

#ifndef DA2324_PROJECT1_RESERVOIR_H
#define DA2324_PROJECT1_RESERVOIR_H

#include <string>
using namespace std;

class Reservoir {
private:
    string name;            // name of the water reservoir
    string municipality;    // municipality where the water reservoir is located
    int id;                 // unique identifier of water reservoir
    string code;            // code of the water reservoir
    int maxDelivery;        // maximum delivery of water reservoir in cubic meters per second
public:
    Reservoir(string name, string municipality, int id, string code, int maxDelivery);
};


#endif //DA2324_PROJECT1_RESERVOIR_H
