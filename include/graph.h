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

    void addDirectedEdge(int id_1, int id_2);
    void addDirectedEdge(int id_1, int id_2, double distance);

    void addEdge(int id_1, int id_2);
    void addEdge(int id_1, int id_2, double distance);

    int addVertex();
    int addVertex(int id, double distance);
    int addVertex(int id);

    bool traverese(int id);

    int getptr() const;

    std::vector< std::vector<int> > findHamiltonCycles();

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


#endif //GRAPHSALG_GRAPH_H
