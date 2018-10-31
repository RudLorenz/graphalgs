#include "graph.h"

#include <iostream>

int main()
{
    Graph glp;

    glp.addVertex();
    glp.addVertex(1);
    glp.addVertex(1);
    glp.addVertex(2);
    glp.addVertex(3);
    glp.addEdge(4, 5);
    glp.addVertex(5);
    glp.addVertex(5);
    glp.addEdge(6, 7);
    glp.addVertex(3);

    std::cout << glp << "\n\n";

    glp.writeasJSON("grph.json");

    std::cout << std::boolalpha;

    std::cout << glp.getptr() << " --> 2 : " << glp.traverese(2) << "\n";
    std::cout << glp.getptr() << " --> 4 : " << glp.traverese(4) << "\n";
    std::cout << glp.getptr() << " --> 5 : " << glp.traverese(5) << "\n";
    std::cout << glp.getptr() << " --> 3 : " << glp.traverese(3) << "\n";
    std::cout << glp.getptr() << " --> 8 : " << glp.traverese(8) << "\n";
    std::cout << "result : " << glp.getptr() << "\n\n";

    for (int i = 0; i < 10; i++)
    {
        if (i == 3) { continue; }
        std::cout << glp.getptr() << " --> " << i <<  " : " << glp.traverese(i) << "\n";
    }

    return 0;
}