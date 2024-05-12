#pragma once

#include <iostream>
#include <stdexcept> 
#include <vector>
#include <list>
#include <unordered_map>

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
private:
	unordered_map<Vertex, list<Edge>> graph;
public:
	Graph() = default;
	~Graph() = default;

    bool has_vertex(const Vertex& v) const {
		return graph.contains(v);
	};
    void add_vertex(const Vertex& v) {
		if (!has_vertex(v)) graph[v] = list<Edge>();
		else throw invalid_argument("Vertex already exists");
	};
    bool remove_vertex(const Vertex& v) {
		return graph.erase(v);
	};
    vector<Vertex> vertices() const {
		vector<Vertex> vec;
		for (auto i : graph) {
			vec.push_back(i.first);
		}
		return vec;
	};

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
		
	};
    bool remove_edge(const Vertex& from, const Vertex& to) {
		
	};
    bool remove_edge(const Edge& e) {
		
	};
    bool has_edge(const Vertex& from, const Vertex& to) const {
		
	};
    bool has_edge(const Edge& e) const {
		
	};

    vector<Edge> edges(const Vertex& vertex) {};

    size_t order() const {};
    size_t degree(const Vertex& v) const {};

    vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {};
    vector<Vertex> walk(const Vertex& start_vertex)const {};

};