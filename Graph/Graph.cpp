#pragma once

#include <iostream>
#include <stdexcept> 
#include <vector>
#include <list>
#include <unordered_map>
#include <queue>
#include <numeric>

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
		auto tmp = graph.find(e.from);
		if (tmp != graph.end()) {
			for (auto tmp_e = (*tmp).second.begin(); tmp_e != (*tmp).second.end(); ++tmp_e) {
				if ((*tmp_e) == e) {
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
			size_t counter = graph[v].size();
			for (auto i : graph) {
				for (auto e : i.second) {
					if (e.to == v) {
						++counter;
					}
				}
			}
			return counter;
		}
		throw invalid_argument("Vertex is not exists");
	};

	void walk(const Vertex& start_vertex)const {
		queue<Vertex> q;
		auto visited = unordered_map<Vertex, int>();
		q.push(start_vertex);
		visited[start_vertex] = 0;
		while (!q.empty()) {
			auto u = q.front();
			q.pop();
			for (auto e : graph.at(u)) {
				auto v = e.to;
				if (visited[v] == 0) {
					visited[v] = visited[u] + 1;
					q.push(v);
				}
			}
		}
	};

	unordered_map<Vertex, Distance> shortest_path(const Vertex& from) const {
		if (graph.contains(from)) {
			size_t size = graph.size();
			unordered_map<Vertex, Distance> distance;
			unordered_map<Vertex, size_t> visited;
			for (const auto& [key, val] : graph) {
				distance[key] = numeric_limits<Distance>::max();
				visited[key] = 0;
			}

			queue<Vertex> q;
			distance[from] = 0;
			q.push(from);

			while (!q.empty()) {
				auto u = q.front();
				q.pop();
				for (auto e : graph.at(u)) {
					if (visited[e.from] == size) {
						break;
					}
					Vertex name = e.to;
					Distance dist = e.dist;
					if (distance[u] + dist < distance[name]) {
						distance[name] = distance[u] + dist;
						++visited[name];
						q.push(name);

					}
				}
			}
			
			return distance;
		}
		else {
			throw invalid_argument("Incorrect input vertex");
		}
	};

	Distance get_eccentricity(const Vertex& vertex) {
		unordered_map<Vertex, Distance> min_distance = shortest_path(vertex);
		Distance ecc = -1;
		for (const auto& [key, val] : min_distance) {
			if (val > ecc) {
				ecc = val;
			}
		}
		return ecc;
	}

	vector<Vertex> find_center() {
		Distance center = numeric_limits<Distance>::max();
		vector<Vertex> names;
		for (const auto& [key, val] : graph) {
			Distance ecc = get_eccentricity(key);
			if (ecc <= center){
				if (ecc < center) {
					names.clear();
				}
				center = ecc;
				names.push_back(key);
			}
		}
		return names;
	}

};