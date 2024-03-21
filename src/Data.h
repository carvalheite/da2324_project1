//
// Created by crvlh8 on 3/21/24.
//

#ifndef DA2324_PROJECT1_DATA_H
#define DA2324_PROJECT1_DATA_H

#include <set>
#include "City.h"
#include "Station.h"
#include "Pipe.h"
#include "Reservoir.h"

using namespace std;

class Data {
private:
    set<City*> cities;
    set<Station*> stations;
    set<Reservoir*> reservoirs;
    set<Pipe*> pipes;

public:
    Data();
    void addCity(City* city);
    void addStation(Station* station);
    void addReservoir(Reservoir* reservoir);
    void addPipe(Pipe* pipe);
    City* getCityCode(string name);
};


#endif //DA2324_PROJECT1_DATA_H
