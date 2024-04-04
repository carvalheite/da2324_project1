//
// Created by crvlh8 on 4/3/24.
//

#ifndef DA2324_PROJECT1_RESERVOIR_H
#define DA2324_PROJECT1_RESERVOIR_H

#include <string>
using namespace std;
class Reservoir {
public:
    Reservoir(string name, string municiality, int id, string code, int maxDelivery);
    string getName() const { return name; }
    string getMuniciality() const { return municipality; }
    int getId() const { return id; }
    string getCode() const { return code; }
    int getMaxDelivery() const { return maxDelivery; }

private:
    string name;
    string municipality;
    int id;
    string code;
    int maxDelivery;
};


#endif //DA2324_PROJECT1_RESERVOIR_H
