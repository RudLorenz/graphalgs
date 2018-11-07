#include "src/graph.h"

#include <iostream>

int main()
{
    Graph glp;

    glp.addVertex();
    glp.addVertex(0);
    glp.addVertex();
    glp.addVertex();
    glp.addEdge(1, 2);
    glp.addEdge(1, 3);
    glp.addEdge(0, 3);
    glp.addVertex(3);
    glp.addVertex(4);
    glp.addEdge(2, 5);

////    glp.writeasJSON("graph.json");

    auto result = glp.findHamiltonCycles();

    for (const auto &item : result)
    {
        for (const auto &item1 : item) {
            std::cout << item1 << " -> ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;

    return 0;
}