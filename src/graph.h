#ifndef GRAPHSALG_GRAPH_H
#define GRAPHSALG_GRAPH_H

#include "vertex.h"

#include <set>
#include <map>
#include <vector>
#include <ostream>
#include <fstream>
#include <sstream>
#include <iostream>

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
    int writeasMatrix(const std::string& filename);

    std::set<Vertex>& operator[](int id);
    const std::set<Vertex>& operator[](int id) const;

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
    else {
        return false;
    }
}


int Graph::getptr() const
{
    return ptr_;
}

int Graph::writeasJSON(const std::string &filename) const
{
    std::ofstream result_file(filename);

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


int Graph::writeasMatrix(const std::string &filename)
{
    std::ofstream result_file(filename);

    if (!result_file.is_open()) {
        return -1;
    }

    double ** result = new double*[vert_.size()];
    result[0] = new double[vert_.size() * vert_.size()];

    for (size_t i = 1; i != vert_.size(); ++i) {
        result[i] = result[i-1] + vert_.size();
    }

    for (const auto &vert : vert_)
    {
        for (size_t i = 0; i < vert_.size(); ++i) {
            result[vert.first-1][i] = 0;
        }

        for (const auto &set_elem : vert.second) {
            result[vert.first-1][set_elem.id-1] = set_elem.distance;
        }
    }

    result_file << vert_.size() << "\n";
    for (size_t i = 0; i < vert_.size(); i++)
    {
        for(size_t j = 0; j < vert_.size(); j++) {
            result_file << result[i][j] << "\t";  // TABS VS SPACES
        }                                         // HERE WE GO AGAIN
        result_file << "\n";
    }

    result_file.close();
    delete[] result[0];
    delete[] result;

    return 0;
}


std::set<Vertex> &Graph::operator[](int id)
{
    return vert_.at(id);
}


const std::set<Vertex> &Graph::operator[](int id) const
{
    return vert_.at(id);
}


#endif //GRAPHSALG_GRAPH_H
