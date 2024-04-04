//
// Created by jose on 26-03-2024.
//

#ifndef DA2324_PROJECT1_VERTEX_H
#define DA2324_PROJECT1_VERTEX_H

#include "Edge.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h"

using namespace std;

class Vertex {
public:
    Vertex(int id, string code) : id(id) , code(code) {}

    bool addPipe(Pipe* pipe);

    // Getter and Setter for id
    int getId() const;
    void setId(int id);

    const string& getCode() const;
    void setCode(const string& code);

    // Getter and Setter for adjacent
    const vector<Pipe*>& getAdjacent() const;
    void setAdjacent(const vector<Pipe*>& adjacent);

    // Getter and Setter for incoming
    const vector<Pipe*>& getIncoming() const;
    void setIncoming(const vector<Pipe*>& incoming);

private:
    int id;
    string code;
    std::vector<Pipe*> adjacent = std::vector<Pipe*>();
    std::vector<Pipe*> incoming = std::vector<Pipe*>();


};



/*
class Reservoir :   public Vertex {
public:
    Reservoir(int id, string code, double maxDelivery, string name, string municipality): Vertex(id, code), maxDelivery(maxDelivery), name(name), municipality(municipality) {}

    // Getter and Setter for MaxDelivery
    double getMaxDelivery() const;
    void setMaxDelivery(double maxDelivery);

    // Getter and Setter for name
    const string& getName() const;
    void setName(const string& name);

    // Getter and Setter for municipality
    const string& getMunicipality() const;
    void setMunicipality(const string& municipality);
private:
    double maxDelivery; // Maximum delivery of water reservoir in m3/sec
    string name;        // Name of the water reservoir
    string municipality; // Municipality where the water reservoir is located
};



class PumpingStation : public Vertex{
public:
    PumpingStation(int id, const string& code) : Vertex(id, code) {}

};



class City : public Vertex {
public:
    City(int id, const string& code, double demand, const string& cityName, int population)
            : Vertex(id, code), demand(demand), cityName(cityName), population(population) {}

    // Getter and Setter for demand
    double getDemand() const;
    void setDemand(double demand);

    // Getter and Setter for cityName
    const string& getCityName() const;
    void setCityName(const string& cityName);

    // Getter and Setter for population
    int getPopulation() const;
    void setPopulation(int population);

private:
    double demand;     // Rate demand or need of delivery site in m3/sec
    string cityName;   // City of the delivery site
    int population;    // Total population of the delivery site
};


*/


#endif //DA2324_PROJECT1_VERTEX_H
