//
// Created by jose on 26-03-2024.
//

#include "Edge.h"

Pipe::Pipe(Vertex *orig, Vertex *dest, double c, int type) {
    this->dest = dest;
    this->orig = orig;
    this->capacity = c;
    if(type==0)setReverse(this);

}

void Pipe::setReverse(Pipe *reverse) {
    this->reverse = new Pipe(reverse->dest,reverse->orig,reverse->capacity,1);
}

Vertex *Pipe::getOrig() const {
    return this->orig;
}

Vertex *Pipe::getDest() const {
    return this->dest;
}

Pipe *Pipe::getReverse() {
    return this->reverse;
}
