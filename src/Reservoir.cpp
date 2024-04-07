//
// Created by crvlh8 on 4/3/24.
//

#include "Reservoir.h"

Reservoir::Reservoir(string name, string municipality, int id, string code, int maxDelivery) {
    this->name = name;
    this->municipality = municipality;
    this->id = id;
    this->code = code;
    this->maxDelivery = maxDelivery;
}

void Reservoir::setMaxDelivery(int delivery) {
    this->maxDelivery = delivery;
}
