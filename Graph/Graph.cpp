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
		if (has_vertex(from) && has_vertex(to)) {
			graph[from].push_back(Edge(from, to, d));
		}
		else {
			throw invalid_argument("Vertex is not exist");
		}
	};
	bool has_edge(const Vertex& from, const Vertex& to) const {
		auto tmp = graph.find(from);
		if (tmp != graph.end()) {
			for (auto tmp_e = (*tmp).second.begin(); tmp_e != (*tmp).second.end(); ++tmp_e) {
				if ((*tmp_e).to == to) {
					return true;
				}
			}
		}
		return false;
	};
	bool has_edge(const Edge& e) const {
		auto iter = graph.find(e.from);
		if (iter != graph.end()) {
			for (auto iter_e = (*iter).second.begin(); iter_e != (*iter).second.end(); ++iter_e) {
				if ((*iter_e) == e) {
					return true;
				}
			}
		}
		return false;
	};

    bool remove_edge(const Vertex& from, const Vertex& to) {
		if (has_edge(from, to)) {
			auto tmp = graph.find(from);
			if (tmp != graph.end()) {
				for (auto tmp_e = (*tmp).second.begin(); tmp_e != (*tmp).second.end(); ++tmp_e) {
					if ((*tmp_e).to == to) {
						graph[from].erase(tmp_e);
						return true;
					}
				}
			}
		}
		return false;
	};
    bool remove_edge(const Edge& e) {
		if (has_edge(e)) {
			auto tmp = graph.find(e.from);
			if (tmp != graph.end()) {
				for (auto tmp_e = (*tmp).second.begin(); tmp_e != (*tmp).second.end(); ++tmp_e) {
					if ((*tmp_e) == e) {
						graph[e.from].erase(tmp_e);
						return true;
					}
				}
			}
		}
		return false;
	};

    vector<Edge> edges(const Vertex& vertex) {
		vector<Edge> edges;
		if (has_vertex(vertex)) {
			for (auto i : graph[vertex]) {
				edges.push_back(i);
			}
		}
		return edges;
	};

    size_t order() const {
		return graph.size();
	};
    size_t degree(const Vertex& v)  {
		if (has_vertex(v)) {
			return graph[v].size();
		}
		throw invalid_argument("Vertex is not exists");
	};

    vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {};
    vector<Vertex> walk(const Vertex& start_vertex)const {};

};