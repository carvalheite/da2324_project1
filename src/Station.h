//
// Created by crvlh8 on 3/21/24.
//

#ifndef DA2324_PROJECT1_STATION_H
#define DA2324_PROJECT1_STATION_H

#include <string>
using namespace std;

class Station {
private:
    int id;         // unique identifier of the pumping station
    string code;    // code of the pumping station
public:
    Station(int id, string code);
};


#endif //DA2324_PROJECT1_STATION_H
