
#include <iostream>
#include "Graph/Graph.cpp"

using namespace std;

int main() {
	Graph<int, int> graph;
	graph.add_vertex(1);
	graph.add_vertex(2);
	graph.add_vertex(3);
	graph.add_edge(1, 2, 5);
	graph.add_edge(1, 3, 8);
	graph.add_edge(2, 1, 4);
	cout << graph.order() << endl;
	cout << graph.degree(1) << endl;
	for (auto i : graph.edges(2)) {
		cout << i;
	}
	for (auto i : graph.edges(1)) {
		cout << i;
	}
    return 0;
}
