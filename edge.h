#ifndef A2_EDGE_H
#define A2_EDGE_H

#include <iostream>

typedef int vertex;

using namespace std;

class EdgeNode {
public:
    EdgeNode(vertex otherVertex, EdgeNode* next, int cost, int length, int speedLimit = 0)
            : m_otherVertex(otherVertex), m_next(next), m_cost(cost), m_length(length), m_speedLimit(speedLimit) {}

    vertex otherVertex() {
        return m_otherVertex;
    }

    EdgeNode* next() {
        return m_next;
    }

    int cost() {
        return m_cost;
    }

    int length() {
        return m_length;
    }

    int speedLimit() {
        return m_speedLimit;
    }

    void setNext(EdgeNode* next) {
        m_next = next;
    }

private:
    int m_otherVertex;
    int m_cost;
    int m_length;
    int m_speedLimit;
    EdgeNode* m_next;
};

#endif //A2_EDGE_H
