//
// Created by crvlh8 on 3/21/24.
//

#ifndef DA2324_PROJECT1_PIPE_H
#define DA2324_PROJECT1_PIPE_H

#include <string>
using namespace std;

class Pipe {
    string pointA;      // source service that can be a water reservoir, a pumping station, or a delivery site
    string pointB;      // target service that can be a water reservoir, a pumping station, or a delivery site
    int capacity;       // maximum capacity of the pipe
    bool bidirectional; // true if the pipe is bidirectional, false otherwise

public:
    Pipe(string pointA, string pointB, int capacity, bool bidirectional);
};


#endif //DA2324_PROJECT1_PIPE_H
