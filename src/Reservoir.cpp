//
// Created by crvlh8 on 3/21/24.
//

#include "Reservoir.h"
#include <utility>

Reservoir::Reservoir(string name, string municipality, int id, string code, int maxDelivery) {
    this->name = std::move(name);
    this->municipality = std::move(municipality);
    this->id = id;
    this->code = std::move(code);
    this->maxDelivery = maxDelivery;
}
