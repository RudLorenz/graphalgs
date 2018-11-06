#include "src/graph.h"

#include <iostream>

int main()
{
    Graph glp;

    glp.addVertex();
    glp.addVertex(1);
    glp.addVertex(1);
    glp.addVertex(2);
    glp.addVertex(3);
    glp.addVertex(5);
    glp.addVertex(5);
    glp.addEdge(6, 7);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(7);
    glp.addVertex(8);
    glp.addVertex(9);

    glp.writeasJSON("graph.json");
    glp.writeasMatrix("bla.txt");

    return 0;
}