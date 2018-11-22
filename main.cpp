#include "graph.h"
#include "CLI11.h"

#include <iostream>
#include <limits>

int main(int argc, char**argv)
{
    CLI::App app{"Some graph algorithms\nIf no MODE flag is supplied program expects adjacency matrix input"};
    std::string filename = "default";
    bool hamilton_mode    = false;
    bool art_points_mode  = false;
    bool interactive_mode = false;

    auto file_option = app.add_option("-f, --file", filename, "Input file with adjacency matrix")
            ->check(CLI::ExistingFile)
            ->group("Input");
    auto interactive_option = app.add_flag("-i, --interactive", interactive_mode, "Input graph in interactive mode")
            ->group("Input");

    app.add_flag("--hamilton", hamilton_mode, "Find and output all hamilton cycles in given graph")
            ->ignore_case()
            ->group("Mode");

    app.add_flag("-a, --artpoints", art_points_mode, "Find and output all articulation points of given graph")
            ->ignore_case()
            ->group("Mode");

    file_option->excludes(interactive_option);
    interactive_option->excludes(file_option);

    CLI11_PARSE(app, argc, argv);

    Graph glp;

    if (*file_option)
    {
//        if (glp.readfromMatrix(filename))
//        {
//            std::cout << "Can't read from file:" << filename << "\n";
//            return -1;
//        }
    }
    else if (*interactive_option)
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

                glp.addDirectedEdge(i, destination);
            }
        }
    }
    else
    {
        std::cout << "Non interactive matrix input\n";
    }

    if (hamilton_mode)
    {
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
    }

    if (art_points_mode)
    {
        auto ap_points = glp.getArticulationPoints();
        if (ap_points.empty()) {
            std::cout << "No articulation points found!\n";
        }
        else
        {
            std::cout << "Articulation points:\n";
            for (const auto &point : ap_points) {
                std::cout << point << " ";
            }
            std::cout << "\n";
        }
    }


    int decision = 0;
    std::cout << "Write graph as JSON [1] or as Matrix[2] or exit[3]?\n";

    std::cin >> decision;
    while(true)
    {
        if (1 == decision)
        {
            glp.writeasJSON("graph.json");
            break;
        }
        if (2 == decision)
        {
            std::cout << "filename: ";
            std::string output_filename;
            std::cin >> output_filename;
            if(!glp.writeasMatrix(output_filename)) {
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