#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    GraphCity g2(12);

    //Regiao 0
    g2.addEdge(0, 1, 1, 1);
    g2.addEdge(0, 2, 1, 1);
    g2.addEdge(1, 3, 1, 1);
    g2.addEdge(1, 4, 1, 1);
    g2.addEdge(2, 4, 1, 1);
    g2.addEdge(3, 4, 1, 1);
    g2.addEdge(4, 5, 1, 1);
    g2.addEdge(1, 0, 1, 1);
    g2.addEdge(2, 0, 1, 1);
    g2.addEdge(3, 1, 1, 1);
    g2.addEdge(4, 1, 1, 1);
    g2.addEdge(4, 2, 1, 1);
    g2.addEdge(4, 3, 1, 1);
    g2.addEdge(5, 4, 1, 1);

    //Regiao 1
    g2.addEdge(6, 7, 1, 1);
    g2.addEdge(7, 6, 1, 1);
    g2.addEdge(6, 8, 1, 1);
    g2.addEdge(8, 6, 1, 1);
    g2.addEdge(7, 8, 1, 1);
    g2.addEdge(8, 7, 1, 1);

    //Regiao 2
    g2.addEdge(9, 10, 1, 1);
    g2.addEdge(10, 9, 1, 1);
    g2.addEdge(10, 11, 1, 1);
    g2.addEdge(11, 10, 1, 1);


    //Entre regiões
    g2.addEdge(6, 2, 1, 1);
    g2.addEdge(2, 6, 1, 1);
    g2.addEdge(6, 5, 1, 1);
    g2.addEdge(5, 6, 1, 1);
    g2.addEdge(6, 9, 1, 1);
    g2.addEdge(9, 6, 1, 1);
    g2.addEdge(9, 2, 1, 1);
    g2.addEdge(2, 9, 1, 1);


    g2.addRegion(0, 0,6);
    g2.addRegion(1, 6,3);
    g2.addRegion(2, 9,3);

    g2.print();

    g2.defineSubwayLine();

    return 0;
}
