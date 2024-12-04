#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    GraphCity g2(9);
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


    g2.addEdge(6, 7, 1, 1);
    g2.addEdge(7, 6, 1, 1);
    g2.addEdge(6, 8, 1, 1);
    g2.addEdge(8, 6, 1, 1);
    g2.addEdge(7, 8, 1, 1);
    g2.addEdge(8, 7, 1, 1);

    g2.print();
    std::cout << "Hello, World!" << std::endl;
    
    cout << g2.findBestStation(0,6);
    return 0;
}
