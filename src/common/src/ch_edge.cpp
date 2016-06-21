#include "./ch_edge.h"
namespace pgRouting
{
namespace contraction {

void Edge::cp_members(const Edge &other, std::ostringstream& log) {
        log << "cp_members of edge\n";
        log << other;
        
        this->cost = other.cost;
        log << "after copying cost of edge\n";
        log << *this;
        this->first = other.first;
        log << "after copying first of edge\n";
        log << *this;
        #if 0
        this->id = other.id;
        log << "after copying id of edge\n";
        log << *this;
        this->source = other.source;
        log << "after copying source of edge\n";
        log << *this;
        this->target = other.target;
        log << "after copying target of edge\n";
        log << *this;
        this->m_contracted_vertices += other.contracted_vertices();
        log << "after adding contracted vertices\n";
        log << *this;
        #endif
        #if 0
        this->source = other.source;
        this->target = other.target;
        this->cost = other.cost;
        this->first = other.first;
        this->m_contracted_vertices += other.contracted_vertices();
        #endif
    }
#if 0
void Edge::cp_members(const Basic_edge &other) {
        this->id = other.id;
        this->source = other.source;
        this->target = other.target;
        this->cost = other.cost;
        this->first = other.first;
    }
#endif
bool Edge::has_contracted_vertices() const {
    if (m_contracted_vertices.size() == 0)
        return false;
    return true; 
}

const Identifiers<int64_t>& Edge::contracted_vertices() const { 
    return m_contracted_vertices; 
}


void Edge::add_contracted_vertex(Vertex& v, int64_t vid) {
    // adding the id(boost graph) of the contracted vertex v
    m_contracted_vertices += vid;

    //adding the ids of the contracted vertices of the given vertex v
    m_contracted_vertices += v.contracted_vertices();

    // empty the contracted vertices of the given vertex v
    v.clear_contracted_vertices();
}

void Edge::add_contracted_edge_vertices(Edge &e) {

    //adding the ids of the contracted vertices of the given edge e
    m_contracted_vertices += e.contracted_vertices();

    // empty the contracted vertices of the given edge e
    e.clear_contracted_vertices();
}

void Edge::add_contracted_vertices(const Edge &e) {

    //adding the ids of the contracted vertices of the given edge e
    m_contracted_vertices += e.contracted_vertices();

}

#if 0
const std::string Edge_c::type_str() const {
    switch (Edge_c::type()) {
        case Edge_c::Edge_type::ordinary:
            return "Ordinary Edge";
        case Edge_c::Edge_type::shortcut:
            return "Shortcut Edge";
        default:
            return "Undefined Edge";
    }
}
#endif


std::ostream& operator <<(std::ostream& os, const Edge& e) {
    os << "{\n    id: " << e.id << ",\n";
    os << "    source: " << e.source << ",\n";
    os << "    target: " << e.target << ",\n";
    os << "    cost: " << e.cost << ",\n";
    os << "    first: " << e.first << ",\n";
    os << "    contracted vertices: ";
    os << e.contracted_vertices();
    // <<  ", type: " << v.type_str();
    //os << ", isDeleted: " << v.isDeleted();
    /*os << " removed_vertices: {";
    for (auto removed_vertex : v.removed_vertices().ids()) {
        os << removed_vertex << ", ";
    }*/
    os << "\n}";
    os << "\n";
    return os;
}
}  // namespace contraction
}  // namespace pgRouting