//
// Created by crvlh8 on 3/21/24.
//

#include "Pipe.h"

Pipe::Pipe(string pointA, string pointB, int capacity, bool bidirectional) {
    this->pointA = std::move(pointA);
    this->pointB = std::move(pointB);
    this->capacity = capacity;
    this->bidirectional = bidirectional;
}
