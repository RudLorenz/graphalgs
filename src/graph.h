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

    void addDirectedEdge(int id_1, int id_2);
    void addDirectedEdge(int id_1, int id_2, double distance);

    void addEdge(int id_1, int id_2);
    void addEdge(int id_1, int id_2, double distance);

    int addVertex();
    int addVertex(int id, double distance);
    int addVertex(int id);

    bool traverese(int id);

    int getptr() const;

    auto findHamiltonCycles();

    int writeasJSON(const std::string& filename) const;
    int writeasMatrix(const std::string& filename);

    int readfromMatrix(const std::string& filename);

    std::set<Vertex>& operator[](int id);
    const std::set<Vertex>& operator[](int id) const;

    friend std::ostream& operator<<(std::ostream& os, const Graph& gp);

private:
    void recursiveHamiltonSearch(int vt, std::vector<bool> &visited, std::vector<int> &path,
                                 std::vector<std::vector<int>> &result);

    int id_gen_ {0};
    int ptr_ {0};
    std::map<int, std::set<Vertex>> vert_;
};


void Graph::addDirectedEdge(int id_1, int id_2)
{
    vert_[id_1].emplace(id_2, 1);
}


void Graph::addDirectedEdge(int id_1, int id_2, double distance)
{
    vert_[id_1].emplace(Vertex(id_2, distance));
}


void Graph::addEdge(int id_1, int id_2)
{
    vert_[id_1].emplace(id_2, 1);
    vert_[id_2].emplace(id_1, 1);
}


void Graph::addEdge(int id_1, int id_2, double distance)
{
    vert_[id_1].emplace(id_2, distance);
    vert_[id_2].emplace(id_1, distance);
}


int Graph::addVertex()
{
    vert_[id_gen_];
    return id_gen_++;
}


int Graph::addVertex(int id, double distance)
{
    int new_id = id_gen_++;

    vert_[id].emplace(new_id, distance);
    vert_[new_id].emplace(id, distance);

    return new_id;
}


int Graph::addVertex(int id)
{
    return addVertex(id, 1);
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
        result << "\t\t{\"id\": " << item.first << ", \"txt\": \"" << item.first << "\"},\n";
    }

    result.seekp(-2, result.cur);
    result << "\n\t],\n";

    result << "\t\"links\": [\n";

    for (const auto &item : vert_)
    {
        for (const auto &set_elem : item.second)
        {
            result << "\t\t{\"source\": " << item.first
                   << ", \"target\": "    << set_elem.id << ""
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
            result[vert.first][i] = 0;
        }

        if (vert.second.empty()) {
            result[vert.first][vert.first] = 1;
        }
        else
        {
            for (const auto &set_elem : vert.second) {
                result[vert.first][set_elem.id] = set_elem.distance;
            }
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


int Graph::readfromMatrix(const std::string &filename)
{
    std::ifstream input(filename);

    if (!input.is_open()) {
        return -1;
    }

    int graph_size = 0;

    input >> graph_size;

    int counter = 0;
    id_gen_ = 0;   // Should I just append the graph content?
    double tmp = 0;


    while (input >> tmp)
    {
        if (tmp != 0) {
            vert_[id_gen_].insert(Vertex(counter, tmp));
        }

        counter++;

        if (counter == graph_size)
        {
            id_gen_++;
            counter = 0;
        }
    }

    input.close();

    return 0;
}


void Graph::recursiveHamiltonSearch(int vt, std::vector<bool> &visited, std::vector<int> &path,
                                    std::vector<std::vector<int>> &result)
{
    if(vert_.size() == path.size())
    {
        bool last_connected_to_first =
                (vert_.at( path.back() ).find( Vertex(path.front(), 1) ) != vert_.at( path.back() ).end());

        if(last_connected_to_first) {
            result.emplace_back(path);
        }
        return;
    }

    for (auto &set_item : vert_.at(vt))
    {
        if (!visited[set_item.id])
        {
            visited[set_item.id] = true;
            path.emplace_back(set_item.id);

            recursiveHamiltonSearch(set_item.id, visited, path, result);

            // backtrack time!
            visited[set_item.id] = false;
            path.pop_back();
        }
    }
}


auto Graph::findHamiltonCycles()
{
    std::vector<std::vector<int>> result;
    // check if graph is connected

    for (const auto &vert : vert_)
    {
        if (vert.second.empty()) {
            return result;
        }
    }

    std::vector<int> path;
    path.reserve(vert_.size());
    path.emplace_back(ptr_);

    std::vector<bool> visited(vert_.size(), false);
    visited[ptr_] = true;

    recursiveHamiltonSearch(ptr_, visited, path, result);

    return result;
}


#endif //GRAPHSALG_GRAPH_H
