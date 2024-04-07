//
// Created by crvlh8 on 4/3/24.
//

#ifndef DA2324_PROJECT1_CITY_H
#define DA2324_PROJECT1_CITY_H

#include <string>

using namespace std;

class City {
public:
    City(string name, int id, string code, double demand, int population);
    string getName() const { return name; }
    int getId() const { return id; }
    string getCode() const { return code; }
    double getDemand() const { return demand; }
    int getPopulation() const { return population; }

private:
    string name;
    int id;
    string code;
    double demand;
    int population;
};


#endif //DA2324_PROJECT1_CITY_H
