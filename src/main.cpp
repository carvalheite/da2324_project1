#include <iostream>
#include "Manager.h"

int main() {
    Manager manager = Manager();

    cout << "Large Graph Elements:" << endl;
    for (auto &i : manager.largeGraph.getVertexVector()) {
        std::cout << i->getCode() << std::endl;
    }

    cout << "Small Graph Elements:" << endl;
    for (auto &i : manager.smallGraph.getVertexVector()) {
        std::cout << i->getCode() << std::endl;
    }

    return 0;
}
