#include "vertex.h"


std::ostream& operator<<(std::ostream& os, const std::set<Vertex>& vc)
{
    for (const auto &item : vc) {
        os << item.id << ", ";
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

