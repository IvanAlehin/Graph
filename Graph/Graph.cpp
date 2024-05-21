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
    bool remove_vertex(const Vertex& v) {//
		if (has_vertex(v)) {
			for (const auto& [key, val] : graph) {
				remove_edge(key, v);
			}
			graph.erase(v);
			return true;
		}
		return false;
		//return graph.erase(v);
	};
    vector<Vertex> vertices() const {
		vector<Vertex> vec;
		for (const auto& [key, val] : graph) {
			vec.push_back(key);
		}
		return vec;
	};

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
		if (has_vertex(from) && has_vertex(to)) graph[from].push_back(Edge(from, to, d));
		else throw invalid_argument("Vertex is not exist");
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
			return graph[v].size();
		}
		throw invalid_argument("Vertex is not exists");
	};

	vector<Vertex> walk(const Vertex& start_vertex)const {//
		queue<Vertex> q;
		auto visited = unordered_map<Vertex, int>();
		vector<Vertex> vec ;
		vec.push_back(start_vertex);
		q.push(start_vertex);
		visited[start_vertex] = 0;
		while (!q.empty()) {
			auto u = q.front();
			q.pop();

			for (auto e : graph.at(u)) {
				auto v = e.to;
				if (visited[v] == 0) {
					visited[v] = visited[u] + 1;
					if(v != start_vertex) vec.push_back(v);
					q.push(v);
				}
			}
		}
		return vec;
	};

	pair<unordered_map<Vertex, Distance>, unordered_map<Vertex, Vertex>> shortest_path(const Vertex& from) const {//
		if (graph.contains(from)) {
			size_t size = graph.size();
			unordered_map<Vertex, Distance> distance;
			unordered_map<Vertex, size_t> visited;
			unordered_map<Vertex, Vertex> prev;
			for (const auto& [key, val] : graph) {
				distance[key] = numeric_limits<Distance>::max();
				visited[key] = 0;
				prev[key] = NULL;
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
						prev[name] = u;
						q.push(name);

					}
				}
			}
			for (const auto& [key, val] : graph) {
				for (auto e : graph.at(key)) {
					Vertex name = e.to;
					Distance dist = e.dist;
					if (distance[key] + dist < distance[name]) {
						throw invalid_argument("Negative cycles");
					}
				}
			}
			return pair(distance,prev);
		}
		else {
			throw invalid_argument("Incorrect input vertex");
		}
	};

	vector<Vertex> shortest_path(const Vertex& from, const Vertex& to) const {
		auto s_path = shortest_path(from).second;
		auto s_dist = shortest_path(from).first;
		Distance dist = s_dist[to];
		cout << "Distance: " << dist<< endl;
		vector<Vertex> path;
		path.push_back(to);

		for (auto v = s_path[to]; v != from; v = s_path[v]) {
			path.push_back(v);
		}

		path.push_back(from);
		reverse(path.begin(), path.end());
		return path;

	}

	Distance get_eccentricity(const Vertex& vertex) {
		unordered_map<Vertex, Distance> min_distance = shortest_path(vertex).first;
		Distance ecc = numeric_limits<Distance>::min();
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
template<typename Vertex>
ostream& operator<<(ostream& os, const vector<Vertex>& vec) {
	for (auto v : vec) {
		os << v <<' ';
	}
	return os;
}