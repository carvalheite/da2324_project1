//
// Created by crvlh8 on 3/21/24.
//

#include "City.h"

City::City(string name, int id, string code, int demand, int population) {
    this->name = std::move(name);
    this->id = id;
    this->code = std::move(code);
    this->demand = demand;
    this->population = population;
}

string City::getCode() {
    return code;
}
