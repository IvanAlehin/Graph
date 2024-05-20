
#include <iostream>
#include "Graph/Graph.cpp"

using namespace std;

int main() {
	Graph<int, int> graph;
	graph.add_vertex(1);
	graph.add_vertex(2);
	graph.add_vertex(3);
	graph.add_vertex(4);
	graph.add_vertex(5);
	graph.add_edge(1, 2, 1);
	graph.add_edge(2, 1, 1);
	graph.add_edge(2, 3, 1);
	graph.add_edge(3, 4, 1);
	graph.add_edge(3, 5, 1);
	graph.add_edge(5, 3, 1);
	graph.add_edge(4, 5, 1);
	graph.add_edge(5, 2, 1);


	cout << graph.order() << endl;
	cout << graph.degree(5) << endl;
	
	for (auto i : graph.shortest_path(1)) {
		cout << i.first << ": "<<i.second<<endl;
	}
	cout << endl;

	for (auto i : graph.find_center()) {
		cout << i << endl;
	}
	cout << endl;

	cout << graph.get_eccentricity(5) << endl;
    return 0;
}
