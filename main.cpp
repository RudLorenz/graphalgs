#include "src/graph.h"

#include <iostream>

int main(int argc, char**argv)
{
    Graph glp;

    if (argc == 2) // assume it's a filename
    {
        if (-1 == glp.readfromMatrix(argv[1]))
        {
            std::cout << "Error reading from file\n";
            return -1;
        }
        std::cout << glp << "\n";
    }
    else // interactive input
    {
        std::cout << "Enter number of vertices:\n";
        int vert_count = 0;
        std::cin >> vert_count;

        if(!std::cin || vert_count <= 0)
        {
            std::cout << "Bad input!\n";
            return -1;
        }

        for (int i = 0; i < vert_count; i++) {
            glp.addVertex();
        }

        for (int i = 0; i < vert_count; i++)
        {
            int adjacent_count = 0;
            std::cout << "Number of adjacent vertices for " << i << ": ";
            std::cin >> adjacent_count;

            if(!std::cin || adjacent_count < 0)
            {
                std::cout << "Bad input!\n";
                return -1;
            }

            for (int j = 0; j < adjacent_count; j++)
            {
                int destination = 0;
                std::cout << i << " --> ";
                std::cin >> destination;
                if(!std::cin || (destination < 0 && destination > vert_count))
                {
                    std::cout << "Bad input!\n";
                    return -1;
                }

                glp.addEdge(i, destination);
            }
        }
    }

    auto result = glp.findHamiltonCycles();

    if (result.empty()) {
        std::cout << "No Hamilton cycles found\n";
    }
    else
    {
        for (const auto &path : result)
        {
            for (const auto &item : path) {
                std::cout << item << " --> ";
            }
            std::cout << "\n";
        }
    }

    int decision = 0;
    std::cout << "Write graph as JSON [1] or as Matrix[2] or don't[3]?\n";

    std::cin >> decision;
    while(1)
    {
        if (1 == decision)
        {
            glp.writeasJSON("graph.json");
            break;
        }
        if (2 == decision)
        {
            std::cout << "filename: ";
            std::string filename;
            std::cin >> filename;
            if(-1 == glp.writeasMatrix(filename)) {
                std::cout << "cant write to file!Try different name\n";
            }
            else {
                break;
            }
        }
        if (3 == decision) {
            break;
        }
        else
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore everything until newline
            std::cout << "Write graph as JSON [1] or as Matrix[2] or don't[3]?\n";
            std::cin >> decision;
        }
    }

    return 0;
}