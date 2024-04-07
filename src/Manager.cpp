//
// Created by jose on 26-03-2024.
//

#include "Manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cfloat>
#include <algorithm>

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

void Manager::printMaxFlow(const vector<pair<City*,double>>& result) {
    std::cout << "*-------------------------------------------*" << std::endl;
    std::cout << "*            CITY MAX FLOW                  *" << std::endl;
    std::cout << "*-------------------------------------------*" << std::endl;
    for (const auto& pair : result) {
        std::cout << "| CITY CODE: " << pair.first->getCode()  << " ----> RESULT: " << pair.second << " |" << std::endl;
    }
    std::cout << "*-------------------------------------------*" << std::endl;
}




vector<pair<City*,double>> Manager::maxWaterFlowForCity(Graph<string> *currGraph, const string& cityCode, const string& graphSize, bool print) {

    auto reservoirMap = (graphSize == "small") ? smallReservoirs : largeReservoirs;
    auto cityMap = (graphSize == "small") ? smallCities : largeCities;
    vector<pair<City*,double>> result;


    if (currGraph->findVertex(cityCode) == nullptr && cityCode != "all") {
        cout << "ERROR: INVALID CITY";
        return result;
    }
    if(cityCode=="all"){
        for(const auto& c : cityMap) {

            edmondsKarp(currGraph,"SuperSource","SuperTarget");
            double maxFlow = calculateMaxFlow<string>(currGraph,c.first);
            result.emplace_back(c.second, maxFlow);

        }
    }
    else {
        City* c = cityMap.at(cityCode);
        edmondsKarp(currGraph,"SuperSource","SuperTarget");
        double maxFlow = calculateMaxFlow<string>(currGraph,cityCode);

        result.emplace_back(c, maxFlow);
    }

    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {return a.first->getId() < b.first->getId();});
    if(print)printMaxFlow(result);
    return result;
}

double findDouble(const vector<pair<string, double>>& vec, const string& str) {
    for (const auto &p: vec) {
        if (p.first == str) {
            return p.second;
        }
    }
    return 0;
}

void Manager::checkWaterDeficit(Graph<string> *currGraph, const string &graphSize) {


    edmondsKarp(currGraph,"SuperSource","SuperTarget");
    vector<pair<City*,double>> result;
    auto cityMap = (graphSize == "small") ? smallCities : largeCities;

    for(auto city : cityMap){
        double  currFlow =0;
        Vertex<string>* v = currGraph->findVertex(city.first);
        for(auto z : v->getIncoming()){currFlow+= z->getFlow();}
        if(city.second->getDemand()>currFlow){result.emplace_back(city.second,city.second->getDemand()-currFlow);}
    }

    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {return a.first->getId() < b.first->getId();});
    printDeficit(result);

}


vector<pair<double,Edge<string>*>> getEdgesDiff(Graph<string> *currGraph){

    vector<pair<double,Edge<string>*>> edgeVector;

    for(auto v : currGraph->getVertexSet()){
        for(auto e : v->getAdj()){
            if(!e->isSelected()){
                edgeVector.emplace_back((e->getWeight()-e->getFlow()),e);
            }
            e->setSelected(true);
        }
    }

    for(auto v : currGraph->getVertexSet()){
        for(auto e : v->getAdj()){
            e->setSelected(false);
        }
    }

    return edgeVector;
}


void printPipes(vector<pair<double, Edge<std::string> *>> pipes){


    std::cout << "*-------------------------------------------*" << std::endl;
    std::cout << "*                 PIPES                     *" << std::endl;
    std::cout << "*-------------------------------------------*" << std::endl;
    for(int i = 0;i<pipes.size();i++){
        cout << "* PIPE CAPACITY: " << pipes[i].second->getFlow() << "/" << pipes[i].second->getWeight() << " FLOW EXCESS: " << pipes[i].first << " *\n";
    }

}

void Manager::balanceNetworkFLow(Graph<string> *currGraph, const string &graphSize) {

    edmondsKarp(currGraph,"SuperSource","SuperTarget");
    auto edgesDiff = getEdgesDiff(currGraph);
    //std::sort(edgesDiff.begin(), edgesDiff.end(), [](const auto& a, const auto& b) {return a.second->getWeight() >  b.second->getWeight();});

    // average difference
    double avgDiff = 0;
    for(int i = 0;i<edgesDiff.size();i++)avgDiff += edgesDiff[i].first;
    avgDiff = avgDiff / edgesDiff.size();
    cout << avgDiff << endl;

    //variance of diff
    double variance = 0;
    for(int i = 0;i<edgesDiff.size();i++)variance += (edgesDiff[i].first - avgDiff)*(edgesDiff[i].first - avgDiff);
    variance = variance / edgesDiff.size();
    cout << variance;

    std::sort(edgesDiff.begin(), edgesDiff.end(), [](const auto& a, const auto& b) {return a.first >  b.first;});


    //printPipes(edgesDiff);
}



void Manager::printDeficit(const vector<pair<City *, double>> &result) {
    std::cout << "*-------------------------------------------*" << std::endl;
    std::cout << "*             DEMAND DEFICIT                *" << std::endl;
    std::cout << "*-------------------------------------------*" << std::endl;
    for (const auto& pair : result) {
        std::cout << "| CITY CODE: " << pair.first->getCode() << " | DEMAND: " << pair.first->getDemand() << " | FLOW: " << pair.first->getDemand() - pair.second << " ----> RESULT: " << pair.second << " |" << std::endl;
    }
    std::cout << "*-------------------------------------------*" << std::endl;
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
