//
// Created by jose on 26-03-2024.
//

#include "Vertex.h"


// Getter and Setter for id
int Vertex::getId() const {
    return id;
}

void Vertex::setId(int id) {
    this->id = id;
}

// Getter and Setter for code
const string& Vertex::getCode() const {
    return code;
}

void Vertex::setCode(const string& code) {
    this->code = code;
}

// Getter and Setter for adjacent
const vector<Pipe*>& Vertex::getAdjacent() const {
    return adjacent;
}

void Vertex::setAdjacent(const vector<Pipe*>& adjacent) {
    this->adjacent = adjacent;
}

// Getter and Setter for incoming
const vector<Pipe*>& Vertex::getIncoming() const {
    return incoming;
}

void Vertex::setIncoming(const vector<Pipe*>& incoming) {
    this->incoming = incoming;
}


// Getter and Setter for MaxDelivery in Reservoir class
double Reservoir::getMaxDelivery() const {
    return maxDelivery;
}

void Reservoir::setMaxDelivery(double maxDelivery) {
    this->maxDelivery = maxDelivery;
}

// Getter and Setter for name in Reservoir class
const string& Reservoir::getName() const {
    return name;
}

void Reservoir::setName(const string& name) {
    this->name = name;
}

// Getter and Setter for municipality in Reservoir class
const string& Reservoir::getMunicipality() const {
    return municipality;
}

void Reservoir::setMunicipality(const string& municipality) {
    this->municipality = municipality;
}

// No additional getter and setter methods for PumpingStation class since it only inherits from Vertex and doesn't add new attributes

// Getter and Setter for demand in City class
double City::getDemand() const {
    return demand;
}

void City::setDemand(double demand) {
    this->demand = demand;
}

// Getter and Setter for cityName in City class
const string& City::getCityName() const {
    return cityName;
}

void City::setCityName(const string& cityName) {
    this->cityName = cityName;
}

// Getter and Setter for population in City class
int City::getPopulation() const {
    return population;
}

void City::setPopulation(int population) {
    this->population = population;
}
