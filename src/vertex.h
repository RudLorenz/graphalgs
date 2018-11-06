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


std::ostream& operator<<(std::ostream& os, const std::set<Vertex>& vc)
{
    for (const auto &item : vc) {
        os << item.id-1 << ", ";
//        os << "(" << item.id << ", dist: " << item.distance << ") ";
    }
    return os;
}


bool operator<(const Vertex &lhs, const Vertex &rhs)
{
    return lhs.id < rhs.id;
}


bool operator>(const Vertex &lhs, const Vertex &rhs)
{
    return lhs.id > rhs.id;
}


bool operator==(const Vertex &lhs, const Vertex &rhs)
{
    return lhs.id == rhs.id;
}


bool operator!=(const Vertex &lhs, const Vertex &rhs)
{
    return lhs.id != rhs.id;
}


#endif //GRAPHSALG_VERTEX_H
