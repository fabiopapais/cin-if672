#include <bits/stdc++.h>
using namespace std;

#define VISITED 1
#define UNVISITED 0
#define INFTY INT_MAX
#define EMPTY -1

class Graph {
public:
    Graph(int n) : adjacency_list(n, vector<pair<int, int>>()), mark(n, UNVISITED), numEdge(0), n(n) {}

    void setMark(int i, int value) {
        mark[i] = value;
    }

    int getMark(int i) {
        return mark[i];
    }

    void setDirectedEdge(int i, int j, int wt) {
        pair<int, int> new_node = pair<int, int>(j, wt);
        adjacency_list[i].push_back(new_node);
        numEdge++;
    }

    void setEdge(int i, int j, int wt) {
        setDirectedEdge(i, j, wt);
        setDirectedEdge(j, i, wt);
    }

    int n;
    vector<vector<pair<int, int>>> adjacency_list;
    int numEdge;
    vector<int> mark;
};

// using tuples to distances min heap structure

struct compare_tuple {
    bool operator()(tuple<int, int, int>& a, tuple<int, int, int>& b) {
        return get<2>(a) > get<2>(b);
    }
};

void dijkstra(Graph& Graph, int source, vector<int>& distance) {
    vector<int> parent(Graph.n, EMPTY); // initializes parents vector
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, compare_tuple> distances_heap; // initializes distances min heap
    for (int i = 0; i < Graph.n; i++) {
        distance[i] = INFTY;
        Graph.setMark(i, UNVISITED);
    }
    distances_heap.push(make_tuple(source, source, 0));
    distance[source] = 0;
    for (int i = 0; i < Graph.n; i++) {
        int p,v;
        do {
            if (distances_heap.empty()) return;
            auto pv = distances_heap.top(); distances_heap.pop();
            p = get<0>(pv); v = get<1>(pv);
        } while (!Graph.getMark(v) == UNVISITED);

        Graph.setMark(v, VISITED); parent[v] = p;

        for (int j = 0; j < Graph.adjacency_list[v].size(); j++) {
            int w = Graph.adjacency_list[v][j].first;
            int weight = Graph.adjacency_list[v][j].second;

            if (Graph.getMark(w) != VISITED && distance[w] > distance[v] + weight) {
                distance[w] = distance[v] + weight;
                distances_heap.push(make_tuple(v, w, distance[w]));
            }
        }

    }
}

int main() {
    int cases; cin >> cases;
    for (int i = 1; i <= cases; i++) {
        int n, m, source, dest;
        cin >> n >> m >> source >> dest;
        Graph graph = Graph(n);
        for (int j = 0; j < m; j++) {
            int node_a, node_b, weight; cin >> node_a >> node_b >> weight;
            graph.setEdge(node_a, node_b, weight);
        }
        vector<int> distances(n);
        dijkstra(graph, source, distances);
        if (distances[dest] != INFTY && distances[dest] != 0) {
            cout << "Case #" << i << ": "  << distances[dest] << endl;
        } else {
            cout << "Case #" << i << ": unreachable" << endl;
        }
    }
    return 0;
}