#include <iostream>
#include "Manager.h"

int main() {
    Manager manager = Manager();

    cout << "Large Graph Elements:" << endl;
    for (auto &i : manager.largeGraph.getVertexSet()) {
        cout << i->getInfo() << endl;
    }

    cout << "Small Graph Elements:" << endl;
    for (auto &i : manager.smallGraph.getVertexSet()) {
        cout << i->getInfo() << endl;
    }

    cout << "Large Graph Pipes:" << endl;
    for (auto &i : manager.largeGraph.getVertexSet()) {
        cout << "All incoming edges to " << i->getInfo() << endl;
        for (auto &edge : i->getIncoming()) {
            cout << edge->getOrig()->getInfo() << " | Capacity: " << edge->getWeight() << endl;
        }
    }

    cout << "Small Graph Pipes:" << endl;
    for (auto &i : manager.smallGraph.getVertexSet()) {
        cout << "All incoming edges to " << i->getInfo() << endl;
        for (auto &edge : i->getIncoming()) {
            cout << edge->getOrig()->getInfo() << " | Capacity: " << edge->getWeight() << endl;
        }
    }


    return 0;
}
