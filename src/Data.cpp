//
// Created by crvlh8 on 3/21/24.
//

#include "Data.h"

Data::Data() = default;

void Data::addCity(City *city) {
    cities.insert(city);
}

void Data::addStation(Station *station) {
    stations.insert(station);
}

void Data::addReservoir(Reservoir *reservoir) {
    reservoirs.insert(reservoir);
}

void Data::addPipe(Pipe *pipe) {
    pipes.insert(pipe);
}

City *Data::getCityCode(string code) {
    for (auto city : cities) {
        if (city->getCode() == code) {
            return city;
        }
    }
    return nullptr;
}
