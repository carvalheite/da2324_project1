//
// Created by jose on 26-03-2024.
//

#include "Graph.h"

bool Graph::addReservoir(int id, const string& code, double maxDelivery, const string& name, string municipality) {
    //CHECK IF EXISTS
    if(findVertex(code)!=nullptr){
        std::cout << "Error: Vertex already exists\n";
        return false;
    }
    Reservoir* reservoir = new Reservoir(id,code,maxDelivery,name,municipality);
    vertexMap.emplace(code, reservoir);
    vertexVector.push_back(reservoir);
    reservoirMap.emplace(code,reservoir);
    reservoirVector.push_back(reservoir);
    return true;
}

bool Graph::addPumpingStation(int id, const std::string& code) {
    //CHECK IF EXISTS
    if (findVertex(code) != nullptr) {
        std::cout << "Error: Vertex already exists\n";
        return false;
    }
    PumpingStation* pumpingstation = new PumpingStation(id, code);
    vertexMap.emplace(code, pumpingstation);
    vertexVector.push_back(pumpingstation);
    pumpingStationMap.emplace(code, pumpingstation);
    pumpingStationVector.push_back(pumpingstation);
    return true;
}

bool Graph::addCity(int id, const string &code, double demand, const string &cityName, int population) {
    if (findVertex(code) != nullptr) {
        std::cout << "Error: Vertex already exists\n";
        return false;
    }
    City* city = new City(id, code,demand,cityName,population);
    vertexMap.emplace(code, city);
    vertexVector.push_back(city);
    cityMap.emplace(code, city);
    cityVertex.push_back(city);
    return true;
}

const std::vector<Vertex *> &Graph::getVertexVector() const {
    return vertexVector;
}

Vertex* Graph::findVertex(const string& code) {
    auto it = vertexMap.find(code);
    if (it == vertexMap.end())
        return nullptr;
    else
        return it->second;
}

const std::unordered_map<std::string, Vertex *> &Graph::getVertexMap() const {
    return vertexMap;
}

// Getter implementation for reservoirs
const std::vector<Reservoir*>& Graph::getReservoirVector() const {
    return reservoirVector;
}

const std::unordered_map<std::string, Reservoir*>& Graph::getReservoirMap() const {
    return reservoirMap;
}

// Getter implementation for pumping stations
const std::vector<PumpingStation*>& Graph::getPumpingStationVector() const {
    return pumpingStationVector;
}

const std::unordered_map<std::string, PumpingStation*>& Graph::getPumpingStationMap() const {
    return pumpingStationMap;
}

// Getter implementation for cities
const std::vector<City*>& Graph::getCityVector() const {
    return cityVertex;
}

const std::unordered_map<std::string, City*>& Graph::getCityMap() const {
    return cityMap;
}

bool Graph::addPipe(const string &codeOrig, const string &codeDest, double capacity, int type) {
    Vertex* origin = findVertex(codeOrig);
    Vertex* dest = findVertex(codeDest);
    if(origin== nullptr || dest == nullptr){cout << "ERROR\n";return false;}
    Pipe* pipe = new Pipe(origin, dest, capacity, type);
    origin->addPipe(pipe);
    if(type==0){origin->addPipe(pipe->getReverse());}


}


