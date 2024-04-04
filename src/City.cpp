//
// Created by crvlh8 on 4/3/24.
//

#include "City.h"

#include <utility>

City::City(string name, int id, string code, double demand, int population) {
    this->name = std::move(name);
    this->id = id;
    this->code = std::move(code);
    this->demand = demand;
    this->population = population;
}


