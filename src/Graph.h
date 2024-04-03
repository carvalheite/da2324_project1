//
// Created by jose on 26-03-2024.
//

#ifndef DA2324_PROJECT1_GRAPH_H
#define DA2324_PROJECT1_GRAPH_H

#include "Vertex.h"

class Graph {
public:
    Graph(){};
    bool addVertex(Vertex v);
    bool addReservoir(int id, const string& code, double maxDelivery, const string& name, string municipality);
    bool addPumpingStation(int id, const std::string& code);
    bool addCity(int id, const string& code, double demand, const string& cityName, int population);

    Vertex* findVertex(const string& code);

    // Getter declarations for reservoirs
    const std::vector<Reservoir*>& getReservoirVector() const;
    const std::unordered_map<std::string, Reservoir*>& getReservoirMap() const;

    // Getter declarations for pumping stations
    const std::vector<PumpingStation*>& getPumpingStationVector() const;
    const std::unordered_map<std::string, PumpingStation*>& getPumpingStationMap() const;

    // Getter declarations for cities
    const std::vector<City*>& getCityVector() const;
    const std::unordered_map<std::string, City*>& getCityMap() const;

    const std::vector<Vertex*>& getVertexVector() const;
    const std::unordered_map<std::string, Vertex*>& getVertexMap() const;

private:
    std::vector<Vertex*> vertexVector;
    std::unordered_map<std::string, Vertex*> vertexMap;
    vector<Reservoir *> reservoirVector = std::vector<Reservoir*>();
    std::unordered_map<std::string,Reservoir*> reservoirMap = std::unordered_map<std::string,Reservoir*>();
    std::vector<PumpingStation*> pumpingStationVector = std::vector<PumpingStation*>();
    std::unordered_map<std::string,PumpingStation*> pumpingStationMap = std::unordered_map<std::string,PumpingStation*>();
    std::vector<City*> cityVertex = std::vector<City*>();
    std::unordered_map<std::string,City*> cityMap = std::unordered_map<std::string,City*>();

};


#endif //DA2324_PROJECT1_GRAPH_H
