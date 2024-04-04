//
// Created by crvlh8 on 4/3/24.
//

#ifndef DA2324_PROJECT1_STATION_H
#define DA2324_PROJECT1_STATION_H

#include <string>

using namespace std;

class Station {
public:
    Station(int id, string code);
    string getCode() const { return code; }
    int getId() const { return id; }
private:
    string code;
    int id;
};


#endif //DA2324_PROJECT1_STATION_H
