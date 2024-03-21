//
// Created by crvlh8 on 3/21/24.
//

#ifndef DA2324_PROJECT1_CITY_H
#define DA2324_PROJECT1_CITY_H

#include <string>
using namespace std;

class City {
private:
    bool operator=(const City& city);
    string name;    // city of the delivery site
    int id;         // unique identifier of the delivery site
    string code;    // code of the delivery site
    int demand;     // rate demand or need of the delivery site in cubic meters per second
    int population; // population of the delivery site
public:
    City(string name, int id, string code, int demand, int population);
    string getCode();
};


#endif //DA2324_PROJECT1_CITY_H
