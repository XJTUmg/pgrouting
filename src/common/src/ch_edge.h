#ifndef CH_EDGE_H
#define CH_EDGE_H

#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include "../../contraction/src/contraction_structs.hpp"
#include "ch_vertex.h"
#if 0
#include "basic_edge.h"
#endif

namespace pgRouting
{
namespace contraction {
class Edge {
 public:
    #if 0
    enum class Edge_type {
        ordinary = 0,
        shortcut,
    };
    Edge_c() : m_deleted(false),m_type(Edge_type::ordinary) { }
    #endif
    Edge() = default;
    //Edge(const Edge &other){cp_members(other);}
    Edge(const pgr_edge_t &other) :
    id(other.id), source(other.source),
    target(other.target), cost(other.cost){}
    Edge(int64_t id, int64_t source, int64_t target, double cost) :
    id(id), source(source),
    target(target), cost(cost), first(true){}
    Edge(int64_t id, int64_t source, int64_t target, double cost, bool first) :
    id(id), source(source),
    target(target), cost(cost), first(first){}
    #if 0
    void cp_members(const Basic_edge &other);
    #endif
    void cp_members(const Edge &other, std::ostringstream& log);
    int64_t id;
    int64_t source;
    int64_t target;
    double cost;
    bool first;
    void add_contracted_vertex(Vertex& v, int64_t vid);
    void add_contracted_edge_vertices(Edge& e);
    void add_contracted_vertices(const Edge& e);
    bool has_contracted_vertices() const;
    void clear_contracted_vertices() { m_contracted_vertices.clear(); }
    #if 0
    inline bool isDeleted() const { return m_deleted; }
    inline Edge_type type() const { return m_type; }
    const std::string type_str() const;
    void add_contracted_vertex(Vertex v);
    inline void set_edge_type(Edge_type etype) { m_type = etype; }
    inline void delete_edge() { m_deleted = true; }
    inline void recover() { m_deleted = false; }
    #endif
    const Identifiers<int64_t>& contracted_vertices() const;
    friend std::ostream& operator <<(std::ostream& os, const Edge& e);
 private:
    Identifiers<int64_t> m_contracted_vertices;
    #if 0
    Edge_type m_type;
    bool m_deleted;
    #endif
};

}  // namespace contraction
}  // namespace pgRouting
#endif