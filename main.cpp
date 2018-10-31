#include "graph.h"

#include <iostream>

int main()
{
//    std::map<int, std::vector<Vertex>> graph;
//    graph.insert( std::pair<int, std::vector<Vertex>>(1, { {2, 1}, {7, 15} }) );
//    graph.insert( std::pair<int, std::vector<Vertex>>(2, { {1, 1}, {3, 4}, {4, 1} }) );
//    graph.insert( std::pair<int, std::vector<Vertex>>(3, { {2, 4} }) );
//    graph.insert( std::pair<int, std::vector<Vertex>>(4, { {2, 1}, {5, 1} }) );
//    graph.insert( std::pair<int, std::vector<Vertex>>(5, { {4, 1}, {6, 8}, {7, 2}}) );
//    graph.insert( std::pair<int, std::vector<Vertex>>(6, { {5, 4} }) );
//    graph.insert( std::pair<int, std::vector<Vertex>>(7, { {1, 15}, {5, 2} }) );
//
//    for (const auto &item : graph) {
//        std::cout << item.first << " : " << item.second << "\n";
//    }

    Graph glp;

//    glp.addVertex();
//    glp.addVertex(1);
//    glp.addVertex(1);
//    glp.addVertex(2);
//    glp.addVertex(3);
//    glp.addEdge(4, 5);
//    glp.addVertex(5);
//    glp.addVertex(5);
//    glp.addEdge(6, 7);
//    glp.addVertex(3);

    glp.addVertex();
    glp.addVertex();
    glp.addVertex();
    glp.addVertex(1);
    glp.addVertex(1);
    glp.addVertex(1);
    glp.addVertex(1);
    glp.addVertex(1);
    glp.addVertex(2);
    glp.addVertex(2);
    glp.addVertex(2);
    glp.addVertex(2);
    glp.addVertex(2);
    glp.addVertex(2);
    glp.addVertex(2);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(3);
    glp.addVertex(3);




    std::cout << glp << "\n\n";

    glp.writeAsJSON("graphy.json");

//    std::cout << std::boolalpha;
//
//    std::cout << glp.getptr() << " --> 2 : " << glp.traverese(2) << "\n";
//    std::cout << glp.getptr() << " --> 4 : " << glp.traverese(4) << "\n";
//    std::cout << glp.getptr() << " --> 5 : " << glp.traverese(5) << "\n";
//    std::cout << glp.getptr() << " --> 3 : " << glp.traverese(3) << "\n";
//    std::cout << glp.getptr() << " --> 8 : " << glp.traverese(8) << "\n";
//    std::cout << "result : " << glp.getptr() << "\n\n";
//
//    for (int i = 0; i < 10; i++)
//    {
//        if (i == 3) { continue; }
//        std::cout << glp.getptr() << " --> " << i <<  " : " << glp.traverese(i) << "\n";
//    }

    return 0;
}