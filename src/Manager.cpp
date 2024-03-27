//
// Created by jose on 26-03-2024.
//

#include "Manager.h"
#include <iostream>
#include <fstream>
#include <string>

bool Manager::loadSmallReservoir() {
    std::ifstream resevoirs;
    string str;
    resevoirs.open("../small_dataset/Reservoirs_Madeira.csv");
    if (resevoirs.is_open()) {
        getline(resevoirs,str);
    } else {
        cout << "Failed to open reservoirs\n";
        return true;
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
    return false;
}

Manager::Manager() {
    loadSmallReservoir();
    loadSmallStations();
    loadSmallCities();
}

bool Manager::loadSmallStations() {
    std::ifstream stations;
    string str;
    stations.open("../small_dataset/Stations_Madeira.csv");
    if (stations.is_open()) {
        getline(stations,str);
    } else {
        cout << "Failed to open stations\n";
        return true;
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
    return false;
}

bool Manager::loadSmallCities() {
    std::ifstream cities;
    string str;

    cities.open("../small_dataset/Cities_Madeira.csv");
    if (cities.is_open()) {
        getline(cities,str);
    } else {
        cout << "Failed to open cities\n";
        return true;
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
    return false;
}
