//
// Created by jose on 26-03-2024.
//

#ifndef DA2324_PROJECT1_MANAGER_H
#define DA2324_PROJECT1_MANAGER_H

#include "Graph.h"

#include <string>
#include <unordered_map>

using namespace std;

class Manager {
public:
    Manager();
    Graph<string> largeGraph;
    Graph<string> smallGraph;

private:
    bool loadSmallReservoir();
    bool loadSmallStations();
    bool loadSmallCities();
    bool loadSmallPipes();

    bool loadLargeReservoir();
    bool loadLargeStations();
    bool loadLargeCities();
    bool loadLargePipes();

    unordered_map<string, Reservoir*> smallReservoirs;
    unordered_map<string, Station*> smallStations;
    unordered_map<string, City*> smallCities;

    unordered_map<string, Reservoir*> largeReservoirs;
    unordered_map<string, Station*> largeStations;
    unordered_map<string, City*> largeCities;

    // Main function implementing the Edmonds-Karp algorithm
    template <class T>
    void edmondsKarp(Graph<T> *g, int source, int target) {
// Find source and target vertices in the graph
        Vertex<T>* s = g->findVertex(source);
        Vertex<T>* t = g->findVertex(target);
// Validate source and target vertices
        if (s == nullptr || t == nullptr || s == t)
            throw std::logic_error("Invalid source and/or target vertex");
// Initialize flow on all edges to 0
        for (auto v : g->getVertexSet()) {
            for (auto e: v->getAdj()) {
                e->setFlow(0);
            }
        }
// While there is an augmenting path, augment the flow along the path
        while( findAugmentingPath(g, s, t) ) {
            double f = findMinResidualAlongPath(s, t);
            augmentFlowAlongPath(s, t, f);
        }
    }
    // Function to find the minimum residual capacity along the augmenting path
    template <class T>
    double findMinResidualAlongPath(Vertex<T> *s, Vertex<T> *t) {
        double f = INF;
// Traverse the augmenting path to find the minimum residual capacity
        for (auto v = t; v != s; ) {
            auto e = v->getPath();
            if (e->getDest() == v) {
                f = std::min(f, e->getWeight() - e->getFlow());
                v = e->getOrig();
            }
            else {
                f = std::min(f, e->getFlow());
                v = e->getDest();
            }
        }
// Return the minimum residual capacity
        return f;
    }
// Function to augment flow along the augmenting path with the given flow value
    template <class T>
    void augmentFlowAlongPath(Vertex<T> *s, Vertex<T> *t, double f) {
// Traverse the augmenting path and update the flow values accordingly
        for (auto v = t; v != s; ) {
            auto e = v->getPath();
            double flow = e->getFlow();
            if (e->getDest() == v) {
                e->setFlow(flow + f);
                v = e->getOrig();
            }
            else {
                e->setFlow(flow - f);
                v = e->getDest();
            }
        }
    }

    // Function to test the given vertex 'w' and visit it if conditions are met
    template <class T>
    void testAndVisit(std::queue< Vertex<T>*> &q, Edge<T> *e, Vertex<T> *w, double residual) {
// Check if the vertex 'w' is not visited and there is residual capacity
        if (! w->isVisited() && residual > 0) {
// Mark 'w' as visited, set the path through which it was reached, and enqueue it
            w->setVisited(true);
            w->setPath(e);
            q.push(w);
        }
    }
// Function to find an augmenting path using Breadth-First Search
    template <class T>
    bool findAugmentingPath(Graph<T> *g, Vertex<T> *s, Vertex<T> *t) {
// Mark all vertices as not visited
        for (auto v: g->getVertexSet()) {
            v->setVisited(false);
        }
// Mark the source vertex as visited and enqueue it
        s->setVisited(true);
        std::queue<Vertex<T> *> q;
        q.push(s);
// BFS to find an augmenting path
        while (!q.empty() && !t->isVisited()) {
            auto v = q.front();
            q.pop();
// Process outgoing edges
            for (auto e: v->getAdj()) {
                testAndVisit(q, e, e->getDest(), e->getWeight() - e->getFlow());
            }
// Process incoming edges
            for (auto e: v->getIncoming()) {
                testAndVisit(q, e, e->getOrig(), e->getFlow());
            }
        }
// Return true if a path to the target is found, false otherwise
        return t->isVisited();
    }
};

#endif //DA2324_PROJECT1_MANAGER_H
