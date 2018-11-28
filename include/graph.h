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

    void delDirectedEdge(int id);
    void delDirectedEdge(int id_1, int id_2);

    void delEdge(int id);
    void delEdge(int id_1, int id_2);

    bool traverese(int id);

    int getptr() const;
    size_t size() const;

    std::vector< std::vector<int> > findHamiltonCycles();

    std::vector<int> getArticulationPoints() const;
    std::vector<int> getArticulationPoints(std::vector<int>& low) const;

    int writeasJSON(const std::string& filename) const;
    int writeasJSON(const std::string& filename, const std::vector<int>& groups) const;
    int writeasMatrix(const std::string& filename);

    int readfromMatrix(const std::string& filename);

    std::set<Vertex>& operator[](int id);
    const std::set<Vertex>& operator[](int id) const;

    friend std::ostream& operator<<(std::ostream& os, const Graph& gp);

private:
    void recursiveHamiltonSearch(int vt, std::vector<bool>& visited, std::vector<int> &path,
                                 std::vector<std::vector<int>>& result);

    void recursiveGetAP(int vt, int current_depth, std::vector<int>& result,
                        std::vector<int>& parent, std::vector<bool>& visited,
                        std::vector<int>& depth,  std::vector<int>& low) const;

    int id_gen_ {0};
    int ptr_ {0};
    std::map<int, std::set<Vertex>> vert_;
};


#endif //GRAPHSALG_GRAPH_H
