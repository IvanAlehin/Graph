
#include <iostream>
#include "Graph/Graph.cpp"

using namespace std;

int main() {
	Graph<int, float> graph;
	graph.add_vertex(1);
	graph.add_vertex(2);
	graph.add_vertex(3);
	cout<<graph.has_vertex(2)<<endl;
	for (auto i : graph.vertices()) {
		cout << i << " ";
	}
	cout << endl;
	graph.remove_vertex(1);
	for (auto i : graph.vertices()) {
		cout << i << " ";
	}
    return 0;
}
