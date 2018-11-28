#include "graph.h"
#include "CLI11.h"

#include <iostream>

int main(int argc, char**argv)
{
    CLI::App app{"Some graph algorithms\nIf no MODE flag is supplied program expects adjacency matrix input"};
    std::string filename;
    std::string output_file;
    bool hamilton_mode    = false;
    bool art_points_mode  = false;
    bool interactive_mode = false;
    bool delete_mode      = false;

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

    app.add_flag("-d, --delete", delete_mode, "Delete articualtion points if any found")
            ->group("Mode")
            ->needs("-a");

    auto file_out_flag = app.add_option("-o, --output", output_file, "Output graph in given a file")
            ->group("Output");
    auto json_out_flag = app.add_flag("-j, --json", "Output graph as a json")
            ->group("Output")
            ->needs(file_out_flag);
    auto matrix_out_flag = app.add_flag("-m, --matrix", "Output graph as a matrix")
            ->group("Output")
            ->needs(file_out_flag);

    json_out_flag->excludes(matrix_out_flag);
    matrix_out_flag->excludes(json_out_flag);

    file_option->excludes(interactive_option);
    interactive_option->excludes(file_option);

    CLI11_PARSE(app, argc, argv);

    Graph glp;

    if (*file_option)
    {
        if (glp.readfromMatrix(filename))
        {
            std::cout << "Can't read from file:" << filename << "\n";
            return -1;
        }
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

        int graph_size;
        std::cin >> graph_size;

        int el_counter = graph_size*graph_size; //si senior estoy contando elementos
        int current_row = 0;
        int counter = 0;
        int tmp;

        for (int i = 0; i < graph_size; i++) {
            glp.addVertex();
        }

        while(std::cin >> tmp && el_counter !=0)
        {
            if (tmp != 0) {
                glp.addEdge(current_row, counter, tmp);
            }
            counter++;
            el_counter--;

            if (counter == graph_size)
            {
                counter = 0;
                current_row++;
            }
        }

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

    std::vector<int> groups(glp.size(), 0);

    if (art_points_mode)
    {
        auto ap_points = glp.getArticulationPoints(groups);
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

        if (delete_mode)
        {
            std::cout << "delete mode\n";
            if (!ap_points.empty())
            {
                for (const auto &item : ap_points) {
                    glp.delVertex(item);
                }
            }
        }
    }

    if (*json_out_flag)
    {
        if (glp.writeasJSON(output_file, groups))
        {
            std::cout << "Error creating " << output_file << " file!\n";
            return -1;
        }
    }
    if (*matrix_out_flag)
    {
        if (glp.writeasMatrix(output_file))
        {
            std::cout << "Error creating " << output_file << " file\n";
            return -1;
        }
    }

    return 0;
}