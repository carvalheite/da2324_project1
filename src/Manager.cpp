//
// Created by jose on 26-03-2024.
//

#include "Manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cfloat>

using namespace std;

Manager::Manager() {
    loadSmallReservoir();
    loadSmallStations();
    loadSmallCities();
    loadSmallPipes();

    loadLargeReservoir();
    loadLargeStations();
    loadLargeCities();
    loadLargePipes();

    adaptSmall();
    adaptLarge();
}

bool Manager::loadSmallReservoir() {
    std::ifstream resevoirs;
    string str;
    resevoirs.open("../small_dataset/Reservoirs_Madeira.csv");
    if (resevoirs.is_open()) {
        getline(resevoirs,str);
    } else {
        cout << "Failed to open reservoirs\n";
        return false;
    }
    while(!resevoirs.eof()) {
        string name, id, municipality, code, maxDelivery,ignore;

        getline(resevoirs, name,',');
        if(name=="")continue;
        getline(resevoirs, municipality,',');
        getline(resevoirs, id,',');
        getline(resevoirs, code,',');
        getline(resevoirs, maxDelivery,',');
        getline(resevoirs, ignore,',');

        smallReservoirs[code] = new Reservoir(name, municipality, stoi(id), code, stoi(maxDelivery));
        smallGraph.addVertex(code);
    }
    resevoirs.close();
    return true;
}

bool Manager::loadSmallStations() {
    std::ifstream stations;
    string str;
    stations.open("../small_dataset/Stations_Madeira.csv");
    if (stations.is_open()) {
        getline(stations,str);
    } else {
        cout << "Failed to open stations\n";
        return false;
    }
    while(!stations.eof()) {
        string id, code,ignore;

        getline(stations, id,',');
        getline(stations, code,',');
        getline(stations, ignore,',');
        if(code=="")continue;

        smallStations[code] = new Station(stoi(id), code);
        smallGraph.addVertex(code);
    }
    stations.close();
    return true;
}

bool Manager::loadSmallCities() {
    std::ifstream cities;
    string str;

    cities.open("../small_dataset/Cities_Madeira.csv");
    if (cities.is_open()) {
        getline(cities,str);
    } else {
        cout << "Failed to open cities\n";
        return false;
    }
    while(!cities.eof()) {
        //city,id,code,demand,population
        string id, code, demand ,population,city;

        getline(cities, city,',');
        getline(cities, id,',');
        getline(cities, code,',');
        getline(cities, demand,',');
        getline(cities, population,'"');
        getline(cities, population,'"');

        if(code=="")continue;

        smallCities[code] = new City(city, stoi(id), code, stod(demand), stoi(population));
        smallGraph.addVertex(code);
    }
    cities.close();
    return true;
}

bool Manager::loadSmallPipes() {
    std::ifstream pipes;
    string str;

    pipes.open("../small_dataset/Pipes_Madeira.csv");
    if (pipes.is_open()) {
        getline(pipes,str);
    } else {
        cout << "Failed to open cities\n";
        return false;
    }
    while(!pipes.eof()) {
        //city,id,code,demand,population
        string serviceA, serviceB, capacity, direction;

        getline(pipes, serviceA,',');
        getline(pipes, serviceB,',');
        getline(pipes, capacity,',');
        getline(pipes, direction);
        if(serviceA.empty())continue;

        if (stoi(direction) == 0) {
            smallGraph.addBidirectionalEdge(serviceA, serviceB, stod(capacity));
        } else if (stoi(direction) == 1) {
            smallGraph.addEdge(serviceA, serviceB, stod(capacity));
        } else {
            cout << "Couldn't add pipe" << endl;
            return false;
        }

    }
    pipes.close();
    return true;
}

bool Manager::loadLargeReservoir() {
    std::ifstream resevoirs;
    string str;
    resevoirs.open("../large_dataset/Reservoir.csv");
    if (resevoirs.is_open()) {
        getline(resevoirs,str);

    } else {
        cout << "Failed to open reservoirs\n";
        return true;
    }
    while(getline(resevoirs, str)) {
        str.erase(std::remove(str.begin(), str.end(), '\r' ), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\n' ), str.end());

        string name, id, municipality, code, maxDelivery;

        std::stringstream ss(str);

        getline(ss, name,',');
        if(name=="")continue;
        getline(ss, municipality,',');
        getline(ss, id,',');
        getline(ss, code,',');
        getline(ss, maxDelivery,',');

        largeGraph.addVertex(code);
        largeReservoirs[code] = new Reservoir(name, municipality, stoi(id), code, stoi(maxDelivery));
    }
    resevoirs.close();
    return false;
}

bool Manager::loadLargeStations() {
    std::ifstream stations;
    string str;
    stations.open("../large_dataset/Stations.csv");
    if (stations.is_open()) {
        getline(stations,str);
    } else {
        cout << "Failed to open stations\n";
        return true;
    }
    while(getline(stations, str)) {
        str.erase(std::remove(str.begin(), str.end(), '\r' ), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\n' ), str.end());

        string id, code;

        std::stringstream ss(str);

        getline(ss, id,',');
        getline(ss, code,',');
        if(code=="")continue;

        largeStations[code] = new Station(stoi(id), code);
        largeGraph.addVertex(code);
    }
    stations.close();
    return false;
}

bool Manager::loadLargeCities() {
    std::ifstream cities;
    string str;

    cities.open("../large_dataset/Cities.csv");
    if (cities.is_open()) {
        getline(cities,str);
    } else {
        cout << "Failed to open cities\n";
        return true;
    }
    while(getline(cities, str)) {
        str.erase(std::remove(str.begin(), str.end(), '\r' ), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\n' ), str.end());

        string id, code, demand, population, city;

        stringstream ss(str);

        getline(ss, city,',');
        getline(ss, id,',');
        getline(ss, code,',');
        getline(ss, demand,',');
        getline(ss, population,',');

        if(code=="")continue;

        largeCities[code] = new City(city, stoi(id), code, stod(demand), stoi(population));
        largeGraph.addVertex(code);
    }
    cities.close();
    return false;
}

bool Manager::loadLargePipes() {
    std::ifstream pipes;
    string str;

    pipes.open("../large_dataset/Pipes.csv");
    if (pipes.is_open()) {
        getline(pipes,str);
    } else {
        cout << "Failed to open cities\n";
        return false;
    }
    while(!pipes.eof()) {
        //city,id,code,demand,population
        string serviceA, serviceB, capacity, direction;

        getline(pipes, serviceA,',');
        getline(pipes, serviceB,',');
        getline(pipes, capacity,',');
        getline(pipes, direction);
        if(serviceA.empty())continue;

        if (stoi(direction) == 0) {
            largeGraph.addBidirectionalEdge(serviceA, serviceB, stod(capacity));
        } else if (stoi(direction) == 1) {
            largeGraph.addEdge(serviceA, serviceB, stod(capacity));
        } else {
            cout << "Couldn't add pipe" << endl;
            return false;
        }
    }
    pipes.close();
    return true;
}

void Manager::adaptSmall() {
    smallGraph.addVertex("SuperSource");
    smallGraph.addVertex("SuperTarget");

    for(auto vertex : smallGraph.getVertexSet()){
        if (vertex->getInfo()[0] == 'R') {
            auto reservoir = smallReservoirs[vertex->getInfo()];
            smallGraph.addEdge("SuperSource", vertex->getInfo(), reservoir->getMaxDelivery());
        }

        else if (vertex->getInfo()[0] == 'C') {
            auto city = smallCities[vertex->getInfo()];
            smallGraph.addEdge(vertex->getInfo(), "SuperTarget", city->getDemand());
        }
    }
}

void Manager::adaptLarge() {
    largeGraph.addVertex("SuperSource");
    largeGraph.addVertex("SuperTarget");

    for(auto vertex : largeGraph.getVertexSet()){
        if (vertex->getInfo()[0] == 'R') {
            auto reservoir = largeReservoirs[vertex->getInfo()];
            largeGraph.addEdge("SuperSource", vertex->getInfo(), reservoir->getMaxDelivery());
        }

        else if (vertex->getInfo()[0] == 'C') {
            auto city = largeCities[vertex->getInfo()];
            largeGraph.addEdge(vertex->getInfo(), "SuperTarget", city->getDemand());
        }
    }
}

void Manager::printMaxFlowResults(const vector<pair<string,double>>& result) {
    std::cout << "*-------------------------------------------*" << std::endl;
    std::cout << "*      MAX FLOW RESULTS                     *" << std::endl;
    std::cout << "*-------------------------------------------*" << std::endl;
    for (const auto& pair : result) {
        std::cout << "| CITY CODE: " << pair.first << " ----> RESULT: " << pair.second << " |" << std::endl;
    }
    std::cout << "*-------------------------------------------*" << std::endl;
}


void Manager::maxWaterFlowForCity(Graph<string> *currGraph, const string& cityCode,const string& graphSize) {

    auto reservoirMap = (graphSize == "small") ? smallReservoirs : largeReservoirs;
    auto cityMap = (graphSize == "small") ? smallCities : largeCities;
    vector<pair<string,double>> result;


    if (currGraph->findVertex(cityCode) == nullptr && cityCode != "all") {
        cout << "ERROR: INVALID CITY";
        return;
    }
    if(cityCode=="all"){
        for(auto c : cityMap) {
            double maxFlow = 0;
            for (auto x: reservoirMap) {
                edmondsKarp(currGraph, x.first, c.first);
                maxFlow = std::max(maxFlow, calculateMaxFlow<string>(currGraph, c.first));
            }
            result.emplace_back(c.first, maxFlow);
        }
    }
    else {
        double maxFlow = 0;
        for (auto x: reservoirMap) {
            edmondsKarp(currGraph, x.first, cityCode);
            maxFlow = std::max(maxFlow, calculateMaxFlow<string>(currGraph, cityCode));
        }
        result.emplace_back(cityCode, maxFlow);
    }

    printMaxFlowResults(result);

}

template <class T>
double Manager::calculateMaxFlow(Graph<string>* g, const string &sink) {
    double maxFlow = 0.0;
    Vertex<T> *sinkVertex = g->findVertex(sink);
    // Iterate through all outgoing edges from the sink vertex
    for (auto e : sinkVertex->getIncoming()) {
        maxFlow += e->getFlow();
    }

    return maxFlow;
}
