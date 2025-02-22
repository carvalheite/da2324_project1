//
// Created by jose on 26-03-2024.
//

#include "Manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cfloat>
#include <set>
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
    while(getline(cities, str)) {
        str.erase(std::remove(str.begin(), str.end(), '\r' ), str.end());
        str.erase(std::remove(str.begin(), str.end(), '\n' ), str.end());

        string id, code, demand, population, city;

        stringstream ss(str);

        getline(ss, city,',');
        getline(ss, id,',');
        getline(ss, code,',');
        getline(ss, demand,',');
        getline(ss, population,'"');
        getline(ss, population,'"');

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
        std::cout << "City Code: " << pair.first->getCode()  << " ----> Result: " << pair.second << std::endl;
    }
    double totalFLow = 0;
    for(auto p : result){totalFLow+=p.second;}
    std::cout << "Total Flow: " << totalFLow << std::endl;

    std::cout << "*-------------------------------------------*" << std::endl<< std::endl;
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






void Manager::balanceNetworkFLow(Graph<string> *currGraph, const string &graphSize) {


    edmondsKarp(currGraph,"SuperSource","SuperTarget");
    double maxFlowBefore = calculateMaxFlow<string >(currGraph,"SuperTarget");
    auto edges = getEdgesDiff(currGraph);

    //metrics before
    double avgDifferenceBefore = 0;
    double varianceBefore = 0;

    for(auto e : edges){avgDifferenceBefore+= e.second->getWeight() - e.second->getFlow();}
    avgDifferenceBefore = avgDifferenceBefore / edges.size();

    for(auto e : edges){
        varianceBefore += (e.second->getWeight() - e.second->getFlow() - avgDifferenceBefore) * (e.second->getWeight() - e.second->getFlow() - avgDifferenceBefore);
    }
    varianceBefore = varianceBefore / edges.size();




    double totalFlow = 0;
    for (auto edge : edges) {
        totalFlow += edge.second->getFlow();
    }
    double averageFlow = totalFlow / edges.size();

    bool balanced = false;
    while (!balanced) {
        balanced = true;
        for (auto edge : edges) {
            double flow = edge.second->getFlow();
            double remainingCapacity = edge.second->getWeight() - flow;
            if (flow > averageFlow && remainingCapacity > 0) {
                auto neighbors = edge.second->getOrig()->getAdj();
                for (auto neighbor : neighbors) {
                    double neighborFlow = neighbor->getFlow();
                    double neighborRemainingCapacity = neighbor->getWeight() - neighborFlow;
                    if (neighborFlow < averageFlow && neighborRemainingCapacity > 0) {
                        double transferFlow = min(flow - averageFlow, min(remainingCapacity, averageFlow - neighborFlow));
                        edge.second->setFlow(flow - transferFlow);
                        neighbor->setFlow(neighborFlow + transferFlow);
                        balanced = false;
                        break;
                    }
                }
            }
            if (!balanced) {
                break;
            }
        }

    }

    //metrics after
    double avgDifferenceAfter = 0;
    double varianceAfter = 0;
    double maxFlowAfter = calculateMaxFlow<string >(currGraph,"SuperTarget");

    for(auto e : edges){avgDifferenceAfter += e.second->getWeight() - e.second->getFlow();}
    avgDifferenceAfter = avgDifferenceAfter / edges.size();

    for(auto e : edges){
        varianceAfter += (e.second->getWeight() - e.second->getFlow() - avgDifferenceAfter) * (e.second->getWeight() - e.second->getFlow() - avgDifferenceAfter);
    }
    varianceAfter = varianceBefore / edges.size();

    printBalanceFlow(avgDifferenceBefore,varianceBefore,avgDifferenceAfter,varianceAfter,maxFlowBefore,maxFlowAfter);

}



void Manager::printDeficit(const vector<pair<City *, double>> &result) {
    std::cout << "*-------------------------------------------*" << std::endl;
    std::cout << "*             DEMAND DEFICIT                *" << std::endl;
    std::cout << "*-------------------------------------------*" << std::endl;
    for (const auto& pair : result) {
        std::cout << "City Code: " << pair.first->getCode() << " | Demand: " << pair.first->getDemand() << " | Flow: " << pair.first->getDemand() - pair.second << " ----> Result: " << pair.second << std::endl;
    }
    std::cout << "*-------------------------------------------*" <<  std::endl << std::endl;
}

void Manager::printBalanceFlow(double before, double before1, double after, double after1, double before2, double after2) {
    std::cout << "*-------------------------------------------*" << std::endl;
    std::cout << "*     BALANCING FLOW METRICS                *" << std::endl;
    std::cout << "*-------------------------------------------*" << std::endl;

    // Print metrics before balancing
    std::cout << "Before Balancing:" << std::endl;
    std::cout << "Average Difference: " << before << std::endl;
    std::cout << "Variance: " << before1 << std::endl;
    std::cout << "Maximum Flow Difference: " << before2 << std::endl;
    std::cout << std::endl;

    // Print metrics after balancing
    std::cout << "After Balancing:" << std::endl;
    std::cout << "Average Difference: " << after << std::endl;
    std::cout << "Variance: " << after1 << std::endl;
    std::cout << "Maximum Flow Difference: " << after2 << std::endl;
    std::cout << "*-------------------------------------------*" << std::endl << std::endl;
}



void Manager::removeReservoirCheckImpact(Graph<std::string> *g) {
    unordered_map<string, City *> *cities;
    unordered_map<string, Reservoir *> *reservoirs;
    set<string> removedReservoirs;
    unordered_map<string, unordered_map<string, double>> reservoirPipeInfo;

    if (g->getVertexSet().size() > 100) {
        cities = &largeCities;
        reservoirs = &largeReservoirs;
    } else {
        cities = &smallCities;
        reservoirs = &smallReservoirs;
    }

    while (true) {
        set<City *> affectedCities;
        string reservoirCode;
        cout << "Which reservoir do you want to remove?" << endl;
        cin >> reservoirCode;
        while (g->findVertex(reservoirCode) == nullptr) {
            cout << "Invalid reservoir code. Please try again." << endl;
            cin >> reservoirCode;
        }
        cout << endl;

        unordered_map<string, double> maxFlowCity;
        unordered_map<string, double> newFlowCity;
        edmondsKarp(g, "SuperSource", "SuperTarget");
        for (const auto& city : *cities) {
            maxFlowCity[city.first] = calculateMaxFlow<string>(g, city.first);
        }

        unordered_map<string, double> originalPipeCapacity;
        for (auto pipe: g->findVertex(reservoirCode)->getAdj()) {
            originalPipeCapacity[pipe->getDest()->getInfo()] = pipe->getWeight();
            pipe->setWeight(0);
        }
        removedReservoirs.insert(reservoirCode);
        reservoirPipeInfo[reservoirCode] = originalPipeCapacity;

        edmondsKarp(g, "SuperSource", "SuperTarget");

        for (const auto& city : *cities) {
            if ((newFlowCity[city.first] = calculateMaxFlow<string>(g, city.first)) < maxFlowCity[city.first]) {
                affectedCities.insert(city.second);
            }
        }

        cout << "Cities affected by the removal of the reservoirs:" << endl;
        for (City *city: affectedCities) {
            cout << city->getCode() << " - " << city->getName() << endl;
            cout << "Original flow: " << maxFlowCity[city->getCode()] << " | New flow: " << newFlowCity[city->getCode()] << endl << endl;
        }

        cout << endl << "Do you want to remove more reservoirs? (Y/N)" << endl;
        char answer;
        cin >> answer;
        while (answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n') {
            cout << "Invalid answer. Please type y)es or (n)o." << endl;
            cin >> answer;
        }
        if (answer == 'N' || answer == 'n') {
            break;
        }
    }

    for (const string& reservoir: removedReservoirs) {
        for (auto pipe: g->findVertex(reservoir)->getAdj()) {
            pipe->setWeight(reservoirPipeInfo[reservoir][pipe->getDest()->getInfo()]);
        }
    }

}

void Manager::removeStationCheckImpact(Graph<string> *g) {
    unordered_map<string, City *> *cities;
    unordered_map<string, Station *> *stations;
    unordered_map<string, int> originalDeliveries;

    if (g->getVertexSet().size() > 100) {
        cities = &largeCities;
        stations = &largeStations;
    } else {
        cities = &smallCities;
        stations = &smallStations;
    }

    cout << "Do you wish to check a single station or all of them?" << endl;
    cout << "1. Single station" << endl << "2. All stations" << endl;
    int option;
    cin >> option;
    while (option != 1 && option != 2) {
        cout << "Invalid option. Please type 1 or 2." << endl;
        cin >> option;
    }

    string stationCode;

    for (const auto& station : *stations) {
        set<City *> affectedCities;

        if (option == 1) {
            cout << "Which station do you want to remove?" << endl;
            cin >> stationCode;
            cout << endl;
        }

        if (option == 2) {
            stationCode = station.first;
            cout << "SELECTED STATION: " << stationCode << endl;
        }

        unordered_map<string, double> maxFlowCity;
        unordered_map<string, double> newFlowCity;

        edmondsKarp(g, "SuperSource", "SuperTarget");
        for (const auto& city : *cities) {
            maxFlowCity[city.first] = calculateMaxFlow<string>(g, city.first);
        }

        unordered_map<string, double> originalPipeCapacity;
        for (auto pipe: g->findVertex(stationCode)->getAdj()) {
            originalPipeCapacity[pipe->getDest()->getInfo()] = pipe->getWeight();
            pipe->setWeight(0);
        }

        edmondsKarp(g, "SuperSource", "SuperTarget");

        for (const auto& city : *cities) {
            if ((newFlowCity[city.first] = calculateMaxFlow<string>(g, city.first)) < maxFlowCity[city.first]) {
                affectedCities.insert(city.second);
            }
        }

        cout << "Cities affected by the removal of the station:" << endl;
        for (City *city: affectedCities) {
            cout << city->getCode() << " - " << city->getName() << endl;
            cout << "Original flow: " << maxFlowCity[city->getCode()] << " | New flow: " << newFlowCity[city->getCode()] << endl << endl;
        }

        for (auto pipe: g->findVertex(stationCode)->getAdj()) {
            pipe->setWeight(originalPipeCapacity[pipe->getDest()->getInfo()]);
        }

        if (option == 1) {
            cout << endl << "Do you want to remove a different station? (Y/N)" << endl;
            char answer;
            cin >> answer;
            while (answer != 'Y' && answer != 'N' && answer != 'y' && answer != 'n') {
                cout << "Invalid answer. Please type y)es or (n)o." << endl;
                cin >> answer;
            }
            if (answer == 'N' || answer == 'n') {
                break;
            }
        }
    }
}

void Manager::removePipeCheckImpact(Graph<string> *g) {
    unordered_map<string, City *> *cities;
    unordered_map<string, int> originalDeliveries;
    set<Edge<string> *> removedPipes;

    if (g->getVertexSet().size() > 100) {
        cities = &largeCities;
    } else {
        cities = &smallCities;
    }

    cout << "Which pipes do you wish to remove? Type 'Q' to stop." << endl
         << "(Format: 'PS_1 PS_2')" << endl;

    while (true) {
        string orig, dest;
        cin >> orig;
        if (orig == "Q" or orig == "q") break;
        cin >> dest;
        if (dest == "Q" or dest == "q") break;

        if (g->findVertex(orig) == nullptr) {
            cout << "Invalid origin station. Please try again." << endl;
            continue;
        }
        if (g->findVertex(dest) == nullptr) {
            cout << "Invalid destination station. Please try again." << endl;
            continue;
        }

        Vertex<string>* origin = g->findVertex(orig);
        Vertex<string>* destination = g->findVertex(dest);

        for (auto &edge: origin->getAdj()) {
            if (edge->getDest() == destination) {
                removedPipes.insert(edge);
                break;
            }
        }
        for (auto &edge: destination->getAdj()) {
            if (edge->getDest() == origin) {
                removedPipes.insert(edge);
                break;
            }
        }


    }

    cout << endl << "The following pipes will be removed: " << endl;

    for (auto pipe: removedPipes) {
        cout << pipe->getOrig()->getInfo() << " -> " << pipe->getDest()->getInfo() << endl;
    }

    set<City *> affectedCities;
    unordered_map<string, double> maxFlowCity;
    unordered_map<string, double> newFlowCity;

    edmondsKarp(g, "SuperSource", "SuperTarget");

    for (const auto& city : *cities) {
        maxFlowCity[city.first] = calculateMaxFlow<string>(g, city.first);
    }

    unordered_map<Edge<string>*, double> originalPipeCapacity;
    for (auto &pipe: removedPipes) {
        originalPipeCapacity[pipe] = pipe->getWeight();
        pipe->setWeight(0);
    }

    edmondsKarp(g, "SuperSource", "SuperTarget");

    for (const auto& city : *cities) {
        if ((newFlowCity[city.first] = calculateMaxFlow<string>(g, city.first)) < maxFlowCity[city.first]) {
            affectedCities.insert(city.second);
        }
    }

    cout << endl;
    if (affectedCities.empty()) cout << "No cities were affected by the removal of the pipe(s).";
    else {
        cout << "Cities affected by the removal of the pipe(s):" << endl;
        for (City *city: affectedCities) {
            cout << city->getCode() << " - " << city->getName() << endl;
            cout << "Original flow: " << maxFlowCity[city->getCode()] << " | New flow: " << newFlowCity[city->getCode()]
                 << endl << endl;
        }
    }

    for (auto pipe: removedPipes) {
        pipe->setWeight(originalPipeCapacity[pipe]);
    }
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
