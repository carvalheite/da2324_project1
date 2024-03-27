//
// Created by jose on 26-03-2024.
//

#include "Manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>



Manager::Manager() {
    loadSmallReservoir();
    loadSmallStations();
    loadSmallCities();
    loadSmallPipes();

    loadLargeReservoir();
    loadLargeStations();
    loadLargeCities();
    loadLargePipes();
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

        smallGraph.addReservoir(stoi(id), code, stoi(maxDelivery), name, municipality);
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


        smallGraph.addPumpingStation(stoi(id), code);
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

        smallGraph.addCity(stoi(id), code,stod(demand),city,stoi(population));
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

        smallGraph.addPipe(serviceA,serviceB,stoi(capacity),direction[0] - '0');
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
        largeGraph.addReservoir(stoi(id), code, stoi(maxDelivery), name, municipality);
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


        largeGraph.addPumpingStation(stoi(id), code);
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

        largeGraph.addCity(stoi(id), code,stod(demand),city,stoi(population));
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

        largeGraph.addPipe(serviceA,serviceB,stoi(capacity),direction[0] - '0');
    }
    pipes.close();
    return true;
}