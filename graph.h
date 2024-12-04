#ifndef A2_GRAPH_H
#define A2_GRAPH_H

#include <iostream>
#include <vector>
#include "heap.h"
#include "edge.h"


typedef int vertex;

using namespace std;

struct region {
    int id;
    vertex v;
    int size;
};

class GraphCity {
public:
    GraphCity(int numVertices);
    ~GraphCity();
    void addEdge(vertex v1, vertex v2,  int cost, int distance);
    void removeEdge(vertex v1, vertex v2);
    int numVertices();
    void print(vertex v0, int regionSize);
    void addRegion(int id, vertex start, int size);
    region getRegion(int index);
    bool isSubGraph(GraphCity & h);
    void cptDijkstra(vertex v0, vertex regionStart,int regionSize, vertex * parent, int * distance, bool useCost);
    vertex findBestStation(vertex v0, int regionSize);
    void initialize(vertex * parent, bool * inTree, int * vertexCost) const;
    void mstPrim(vertex * parent);
    GraphCity createSubGraph(vector<vertex> stations, vertex ** parents);
    void defineSubwayLine();

private:
    int m_numVertices;
    int m_numEdges;
    vector<region> m_regions;  //(start, size)
    EdgeNode** m_edges;
};

GraphCity::GraphCity(int numVertices)
        : m_numVertices(numVertices), m_numEdges(0), m_edges(nullptr) {
    m_edges = new EdgeNode*[numVertices];
    for (vertex i = 0; i < numVertices; i++) {
        m_edges[i] = nullptr;
    }
}

GraphCity::~GraphCity() {
    for (vertex i = 0; i < m_numVertices; i++) {
        EdgeNode* edge = m_edges[i];
        while (edge) {
            EdgeNode* next = edge->next();
            delete edge;
            edge = next;
        }
    }
    delete[] m_edges;
}

void GraphCity::addEdge(vertex v1, vertex v2, int cost = 0, int distance = 0) {

    EdgeNode* edge = m_edges[v1];
    while (edge) {
        if (edge->otherVertex() == v2) { // Check if edge exists
            return;
        }
        edge = edge->next();
    }
    m_edges[v1] = new EdgeNode(v2, m_edges[v1], cost, distance); // Create the new edge
    m_numEdges++;
}

void GraphCity::removeEdge(vertex v1, vertex v2) {

    EdgeNode* edge = m_edges[v1];
    EdgeNode* previousEdge = nullptr;
    while (edge) {
        if (edge->otherVertex() == v2) { // Found edge
            if (previousEdge) {
                previousEdge->setNext(edge->next());
            } else {
                m_edges[v1] = edge->next();
            }
            delete edge;
            break;
        }
        previousEdge = edge;
        edge = edge->next();
    }
}

int GraphCity::numVertices(){
    return m_numVertices;
}

void GraphCity::print(vertex v0 = 0, int regionSize = -1) {
    if (regionSize == -1) {
        regionSize = m_numVertices;
    }
    for (vertex i = v0; i < v0 + regionSize; ++i) {
        EdgeNode* edge = m_edges[i];
        while (edge) {
            printf("(%d,%d) ", i, edge->otherVertex());
            edge = edge->next();
        }
        printf("\n");
    }
}

void GraphCity::addRegion(int id, vertex start, int size) {
    region r;
    r.id = id;
    r.v = start;
    r.size = size;

    m_regions.push_back(r);
}

region GraphCity::getRegion(int index) {
    if (index >= 0 && index < m_regions.size()) {
        return m_regions[index];
    }
    return {-1, -1}; // Região inválida
}

bool GraphCity::isSubGraph(GraphCity & h) {
    EdgeNode ** hEdges = h.m_edges;
    for (vertex i=0; i < m_numVertices; i++) { // For each vertex
        EdgeNode * hEdge = hEdges[i];
        while (hEdge) { // For each edge in H
            EdgeNode * gEdge = m_edges[i];
            bool found = false;
            while (gEdge) { // Check if it exists in G
                if (hEdge->otherVertex() == gEdge->otherVertex()) {
                    found = true;
                    break;
                }
                gEdge = gEdge->next();
            }
            if (!found) { return false; }
            hEdge = hEdge->next();
        }
    }
    return true;
}

void GraphCity::cptDijkstra(vertex v0, vertex regionStart,int regionSize, vertex * parent, int * distance, bool useCost) {
    bool checked[regionSize];
    Heap heap; // Create the heap
    for (vertex v=0; v < regionSize; v++) {
        parent[v] = -1;
        distance[v] = INT_MAX;
        checked[v] = false;
    }
    parent[v0 - regionStart] = v0;
    distance[v0 - regionStart] = 0;
    heap.insert_or_update(distance[v0], v0);
    while (!heap.empty()) {
        vertex v1 = heap.top().second; // Min vertex
        vertex indexV1 = v1 - regionStart;
        heap.pop(); // Remove from heap
        if (distance[indexV1] == INT_MAX) { break; }
        EdgeNode * edge = m_edges[v1];
        while(edge) {
            vertex v2 = edge->otherVertex();
            if (v2 < regionStart || v2 >= v0 + regionSize) // Considerar apenas dentro da região
            {
                edge = edge->next();
                continue;
            }
            vertex indexV2 = v2 - regionStart;
            if (!checked[indexV2]) {
                int weight = useCost ? edge->cost() : edge->distance(); // Escolhe o peso com base no parâmetro
                if (distance[indexV1] + weight < distance[indexV2]) {
                    parent[indexV2] = v1;
                    distance[indexV2] = distance[indexV1] + weight;
                    heap.insert_or_update(distance[indexV2], v2);
                }
            }
            edge = edge->next();
        }
        checked[v1] = true;
    }
}

vertex GraphCity::findBestStation(vertex v0, int regionSize) {
    vertex parent[m_numVertices];
    int ** distance;
    distance = new int*[m_numVertices];

    for (vertex v=0; v < regionSize; v++) {
        distance[v] = new int[regionSize];
        for (vertex u=0; u < regionSize; u++) {
            distance[v][u] = -1;
        }
    }

    for (vertex v=0; v < regionSize; v++) {
        cptDijkstra(v + v0, v0, regionSize, parent, distance[v], false);
    }

    // Para cada vértice encontra a maior distância entre ele e os outros vértices
    // Destas distâncias retorna a menor
    int minCost = INT_MAX;
    vertex bestStation = -1;

    for (int v = 0; v < regionSize; ++v) {
        int distFurthestVertex = INT_MIN;
        for (int u = 0; u < regionSize; ++u) {
            if(distance[v][u] > distFurthestVertex) distFurthestVertex = distance[v][u];
        }
        if (distFurthestVertex < minCost) {
            minCost = distFurthestVertex;
            bestStation = v + v0;
        }
    }

    return bestStation;
}

void GraphCity::initialize(vertex * parent, bool * inTree, int * vertexCost) const {
    for (vertex v=0; v < m_numVertices; v++) {
        parent[v] = -1;
        inTree[v] = false;
        vertexCost[v] = INT_MAX;
    }
    parent[0] = 0;
    inTree[0] = true;
    EdgeNode * edge = m_edges[0];
    while(edge) {
        vertex v2 = edge->otherVertex();
        parent[v2] = 0;
        vertexCost[v2] = edge->cost();
        edge = edge->next();
    }
}

void GraphCity::mstPrim(vertex * parent) {
    bool inTree[m_numVertices];
    int vertexCost[m_numVertices];
    initialize(parent, inTree, vertexCost);
    Heap heap; // Create the heap
    for (vertex v = 1; v < m_numVertices; v++) { heap.insert_or_update(vertexCost[v], v); }
    while (!heap.empty()) {
        vertex v1 = heap.top().second; // Min vertex
        heap.pop(); // Remove from heap
        if (vertexCost[v1] == INT_MAX) { break; }
        inTree[v1] = true;
        EdgeNode * edge = m_edges[v1];
        while(edge) {
            vertex v2 = edge->otherVertex();
            int cost = edge->cost();
            if (!inTree[v2] && cost < vertexCost[v2]) {
                vertexCost[v2] = cost;
                parent[v2] = v1;
                heap.insert_or_update(vertexCost[v2], v2);
            }
            edge = edge->next();
        }
    }
}

GraphCity GraphCity::createSubGraph(vector<vertex> stations, vertex ** parents = nullptr) {
    int n = stations.size();

    GraphCity SubwayGraph(n);

    for (int i = 0; i < n; ++i) {

        parents[i] = new vertex[m_numVertices];
        int distance[m_numVertices];

        int id1 = getRegion(i).id;
        vertex v1 = stations[i];

        cptDijkstra(v1, 0, m_numVertices, parents[i], distance, true);

        for(int j = 0; j < n; j++){
            if (i == j) continue;

            int id2 = getRegion(j).id;
            vertex v2 = stations[j];

            SubwayGraph.addEdge(id1, id2, distance[v2]);
        }
    }

    return SubwayGraph;
}


void GraphCity::defineSubwayLine() {
    vector<vertex> stations;
    for (const auto& region : m_regions) {
        vertex start = region.v;
        int size = region.size;
        stations.push_back(findBestStation(start, size));
    }

    int numStations = stations.size();

    vertex ** parentCity;
    parentCity = new vertex*[numStations];

    GraphCity subGraph = createSubGraph(stations, parentCity);

    vertex parentSubway[numStations];
    subGraph.mstPrim(parentSubway);

    for(int i = 0; i < numStations; i++)
    {
        if(i != parentSubway[i])
        {
            vertex start = stations[i];
            vertex end = stations[parentSubway[i]];

            while (start != end)
            {
                cout << end << " " << parentCity[i][end] << "\n";
                end = parentCity[i][end];
            }
            cout << "--\n";
        }
    }

}




#endif //A2_GRAPH_H

