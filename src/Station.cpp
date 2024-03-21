//
// Created by crvlh8 on 3/21/24.
//

#include "Station.h"

Station::Station(int id, string code) {
    this->id = id;
    this->code = std::move(code);
}
