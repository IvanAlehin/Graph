#pragma once

#include <iostream>
#include <stdexcept> 

using namespace std;


template<typename Vertex, typename Distance = double>
class Graph {
public:
	struct Edge {
		Vertex from, to;
		Distance dist;
		Edge(const Vertex& from, const Vertex& to, const Distance& dist) : from(from), to(to), dist(dist) {};

		bool operator==(const Edge& other) const {
			return (from == other.from && to == other.to && dist == other.dist);
		}

		friend ostream& operator<<(ostream& os, const Edge& edge) {
			os << edge.from << " -> " << edge.to << " : " << edge.dist << endl;
			return os;
		}
	};

    bool has_vertex(const Vertex& v) const {};
    void add_vertex(const Vertex& v) {};
    bool remove_vertex(const Vertex& v) {};
    std::vector<Vertex> vertices() const {};

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {};
    bool remove_edge(const Vertex& from, const Vertex& to) {};
    bool remove_edge(const Edge& e) {};
    bool has_edge(const Vertex& from, const Vertex& to) const {};
    bool has_edge(const Edge& e) const {};
    std::vector<Edge> edges(const Vertex& vertex) {};

    size_t order() const {};
    size_t degree(const Vertex& v) const {};

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {};
    std::vector<Vertex> walk(const Vertex& start_vertex)const {};

};