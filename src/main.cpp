#include <iostream>
#include "Manager.h"

int main() {
    Manager manager = Manager();

    cout << "Large Graph Elements:" << endl;
    for (auto &i : manager.largeGraph.getVertexVector()) {
        cout << i->getCode() << endl << i->getAdjacent().size() << endl;
    }

    cout << "Small Graph Elements:" << endl;
    for (auto &i : manager.smallGraph.getVertexVector()) {
        cout << i->getCode() << endl << i->getAdjacent().size() << endl;
    }

    return 0;
}
