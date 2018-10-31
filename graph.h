#ifndef GRAPHSALG_GRAPH_H
#define GRAPHSALG_GRAPH_H

#include "vertex.h"

#include <set>
#include <map>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>

class Graph
{
public:
    Graph() = default;
    Graph(const Graph& gp) = default;

    void addEdge(int id_1, int id_2, double distance);
    void addEdge(int id_1, int id_2);

    void addVertex();
    void addVertex(int id, double distance);
    void addVertex(int id);

    bool traverese(int id);

    int getptr() const;

    int writeasJSON(const std::string& filename) const;

    friend std::ostream& operator<<(std::ostream& os, const Graph& gp);

private:
    int id_gen_ {1};
    int ptr_ {1};
    std::map<int, std::set<Vertex>> vert_;
};


void Graph::addEdge(int id_1, int id_2, double distance)
{
    vert_[id_1].emplace(Vertex(id_2, distance));
    vert_[id_2].emplace(Vertex(id_1, distance));
}


void Graph::addEdge(int id_1, int id_2)
{
    vert_[id_1].emplace(id_2, 1);
    vert_[id_2].emplace(id_1, 1);
}


void Graph::addVertex()
{
    vert_[id_gen_++];
}


void Graph::addVertex(int id, double distance)
{
    int new_id = id_gen_++;

    vert_[id].emplace(new_id, distance);
    vert_[new_id].emplace(id, distance);
}


void Graph::addVertex(int id)
{
    addVertex(id, 1);
}


std::ostream &operator<<(std::ostream &os, const Graph &gp)
{
    os << "ptr : " << gp.ptr_ << "\n";

    for (const auto &item : gp.vert_) {
        os << item .first << " : " << item.second << "\n";
    }

    return os;
}

bool Graph::traverese(int id)
{
    auto search = vert_[ptr_].find(Vertex(id, 1));
    if (search != vert_[ptr_].end())
    {
        ptr_ = id;
        return true;
    }
    else
    {
        return false;
    }
}


int Graph::getptr() const
{
    return ptr_;
}

int Graph::writeasJSON(const std::string &filename) const
{
    std::ofstream result_file;
    result_file.open(filename);

    std::stringstream result;

    if (!result_file.is_open()) {
        return -1;
    }

    result << "{\n";
    result << "\t\"nodes\": [\n";
    for (const auto &item : vert_) {
        result << "\t\t{\"id\": " << item.first-1 << ", \"txt\": \"" << item.first-1 << "\"},\n";
    }

    result.seekp(-2, result.cur);
    result << "\n\t],\n";

    result << "\t\"links\": [\n";

    for (const auto &item : vert_)
    {
        for (const auto &set_elem : item.second)
        {
            result << "\t\t{\"source\": " << item.first-1
                   << ", \"target\": "    << set_elem.id-1 << ""
                   //<< "\", \"value\": "       << set_elem.distance
                   << "},\n";
        }
    }

    result.seekp(-2, result.cur);
    result << "\n\t]\n}";

    result_file << result.rdbuf();
    result_file.close();

    return 0;
}


#endif //GRAPHSALG_GRAPH_H
