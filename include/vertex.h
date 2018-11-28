#ifndef GRAPHSALG_VERTEX_H
#define GRAPHSALG_VERTEX_H

#include <ostream>
#include <set>

struct Vertex
{
    Vertex(int i, double d) : id(i), distance(d) {};
    int id;
    double distance;

    friend bool operator< (const Vertex& lhs, const Vertex& rhs);
    friend bool operator> (const Vertex& lhs, const Vertex& rhs);
    friend bool operator==(const Vertex& lhs, const Vertex& rhs);
    friend bool operator!=(const Vertex& lhs, const Vertex& rhs);
};


std::ostream& operator<<(std::ostream& os, const std::set<Vertex>& vc);


#endif //GRAPHSALG_VERTEX_H
