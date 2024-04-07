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

    void adaptSmall();
    void adaptLarge();

    unordered_map<string, Reservoir*> smallReservoirs;
    unordered_map<string, Station*> smallStations;
    unordered_map<string, City*> smallCities;

    unordered_map<string, Reservoir*> largeReservoirs;
    unordered_map<string, Station*> largeStations;
    unordered_map<string, City*> largeCities;

public:

    //[T2.1: 4.0 points] Determine the maximum amount of water that can reach each or a specific city

    /**
    * @brief Calculates and returns the maximum water flow for each city.
    *
    * This function calculates the maximum water flow for each city in the network
    * and returns the result. It also optionally prints the maximum flow for each city.
    *
    * @param currGraph Pointer to the graph representing the water supply network.
    * @param cityCode The code of the city for which to calculate the maximum flow, or "all" to calculate for all cities.
    * @param graphSize The size of the graph ("small" or "large").
    * @param print Flag indicating whether to print the maximum flow for each city.
    * @return A vector containing pairs of cities and their corresponding maximum flows.
    */
    vector<pair<City *, double>> maxWaterFlowForCity(Graph<string> *currGraph, const string& cityCode, const string& graphSize, bool print);

    /**
    * @brief Prints the maximum flow for each city.
    *
    * This function prints the maximum flow for each city in the network,
    * along with the total flow across all cities.
    *
    * @param result A vector containing pairs of cities and their corresponding maximum flows.
    */
    static void printMaxFlow(const vector<pair<City*,double>>& result);


    //[T2.2: 1.0 point]

    /**
    * @brief Checks for water deficit in each city and prints the result.
    *
    * This function calculates the water deficit for each city by comparing the city's
    * demand with the actual flow received. It then prints the deficit for each city.
    *
    * @param currGraph Pointer to the graph representing the water supply network.
    * @param graphSize The size of the graph ("small" or "large").
    */
    void checkWaterDeficit(Graph<string> *currGraph,const string& graphSize);

    /**
     * @brief Prints demand deficit information for cities.
     *
     * This function prints demand deficit information for cities, given a vector of pairs
     * containing pointers to City objects and their corresponding deficit values.
     *
     * @param result A vector of pairs containing pointers to City objects and their deficit values.
     *               Each pair consists of a pointer to a City object and the deficit value (demand - flow).
     */
    static void printDeficit(const vector<pair<City*,double>>& result);


    //[T2.3: 3.0 points]

    /**
     * @brief Balances the network flow in the given graph using the Edmonds-Karp algorithm.
     *
     * This function balances the network flow in the given graph by adjusting the flow
     * across edges to achieve a more uniform distribution of flow. It first calculates
     * the maximum flow in the graph before balancing and then iteratively adjusts the
     * flow until it reaches a more balanced state.
     *
     * @param currGraph A pointer to the graph to be balanced.
     * @param graphSize The size of the graph.
     */
    void balanceNetworkFLow(Graph<string> *currGraph, const string &graphSize);


    /**
     * @brief Prints the metrics related to balancing flow in the network.
     *
     * This function prints the metrics related to balancing flow in the network,
     * including average difference, variance, and maximum flow difference, before
     * and after the balancing process.
     *
     * @param before The average difference before balancing.
     * @param before1 The variance before balancing.
     * @param after The average difference after balancing.
     * @param after1 The variance after balancing.
     * @param before2 The maximum difference before balancing.
     * @param after2 The maximum flow difference after balancing.
     */
    static void printBalanceFlow(double before, double before1, double after, double after1, double before2, double after2);


    /**
     * @brief Calculates the maximum flow reaching the specified sink vertex in the graph.
     *
     * This function calculates the maximum flow reaching the specified sink vertex in the graph.
     * It iterates through all incoming edges to the sink vertex and accumulates the flow on those edges.
     *
     * @tparam T The type of data held by the vertices in the graph.
     * @param g A pointer to the graph in which the maximum flow is to be calculated.
     * @param sink The identifier of the sink vertex for which the maximum flow is calculated.
     * @return The maximum flow reaching the specified sink vertex.
     */
    template <class T>
    double calculateMaxFlow(Graph<string>* g, const string &sink);


    //[T3.1: 2.0 points] Evaluate what happens if one specific water reservoir is out of commission
    void removeReservoirCheckImpact(Graph<string> *g);

    //[T3.2: 2.0 points] Evaluate what happens when pumping stations are removed from the network
    void removeStationCheckImpact(Graph<string> *g);

    //[T3.3: 2.0 points] Evaluate what happens when pipes are removed from the network
    void removePipeCheckImpact(Graph<string> *g);

    // Main function implementing the Edmonds-Karp algorithm
    template <class T>
    void edmondsKarp(Graph<T> *g, string source, string target){
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
