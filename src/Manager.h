//
// Created by jose on 26-03-2024.
//

#ifndef DA2324_PROJECT1_MANAGER_H
#define DA2324_PROJECT1_MANAGER_H

#include "Graph.h"

class Manager {
public:
    Manager();
    Graph largeGraph;
    Graph smallGraph;

private:
    bool loadSmallReservoir();
    bool loadSmallStations();
    bool loadSmallCities();
    bool loadSmallPipes();

    bool loadLargeReservoir();
    bool loadLargeStations();
    bool loadLargeCities();
    bool loadLargePipes();
};


#endif //DA2324_PROJECT1_MANAGER_H
