#include <iostream>
#include "Manager.h"

int main() {
    Manager manager = Manager();

    /*cout << "Large Graph Elements:" << endl;
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
    }*/

    /*cout << "Small Graph SuperSource:" << endl;

    auto smallSuperSource = manager.smallGraph.findVertex("SuperSource");
    for (auto edge : smallSuperSource->getAdj()) {
        cout << edge->getOrig()->getInfo() << " to " << edge->getDest()->getInfo() << endl;
    }

    cout << "Small Graph SuperTarget:" << endl;

    auto smallSuperTarget = manager.smallGraph.findVertex("SuperTarget");
    for (auto edge : smallSuperTarget->getIncoming()) {
        cout << edge->getOrig()->getInfo() << " to " << edge->getDest()->getInfo() << endl;
    }

    cout << "Large Graph SuperSource:" << endl;

    auto largeSuperSource = manager.largeGraph.findVertex("SuperSource");
    for (auto edge : largeSuperSource->getAdj()) {
        cout << edge->getOrig()->getInfo() << " to " << edge->getDest()->getInfo() << endl;
    }

    cout << "Small Graph SuperTarget:" << endl;

    auto largeSuperTarget = manager.largeGraph.findVertex("SuperTarget");
    for (auto edge : largeSuperTarget->getIncoming()) {
        cout << edge->getOrig()->getInfo() << " to " << edge->getDest()->getInfo() << endl;
    }*/

    /*Graph<string> *small = &manager.smallGraph;
    Graph<string> *large = &manager.largeGraph;

    cout << "Number of elements (small):" << endl << small->getVertexSet().size() << endl;
    cout << "Number of elements (large):" << endl << large->getVertexSet().size() << endl;*/
   // manager.maxWaterFlowForCity(small,"all","small");


    return 0;
}
