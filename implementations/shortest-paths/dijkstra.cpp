#include <bits/stdc++.h>
using namespace std;

#define VISITED 1
#define UNVISITED 0
#define INFTY INT_MAX
#define EMPTY -1

// directed/nondirected graph implementation
class Graph {
public:
    // first: node index, second: edge weight
    Graph(int n) : adjacency_list(n, vector<pair<int, int>>()), mark(n, UNVISITED), numEdge(0), n(n) {}

    int e() { return numEdge; } 

    void setMark(int i, int value) {
        mark[i] = value;
    }

    int getMark(int i) {
        return mark[i];
    }
    
    // returns the first connected node index, if any
    int first(int v) {
        if (adjacency_list[v].size() > 0) {
            return adjacency_list[v][0].first;
        }
        return n;
    }

    int weight(int i, int j) {
        for (int k = 0; k < adjacency_list[i].size(); k++) {
            if (adjacency_list[i][k].first == j) {
                return adjacency_list[i][k].second;
            }
        }
        return INFTY; // avoid g++ warnings
    }

    // returns the first connected node index after w, if any
    int next(int v, int w) {
    for (int i = 0; i < adjacency_list[v].size(); i++) {
        if (adjacency_list[v][i].first == w) {
            if (i + 1 < adjacency_list[v].size()) { // next index is in the limit
                return adjacency_list[v][i + 1].first; // returns the next element
            } else {
                break;
            }
        }
    }
    return n;
}

    // sets connection with weight wt at [i][j]
    void setDirectedEdge(int i, int j, int wt) {
        if (wt == 0) return; // "error"

        int adjacency_node_size = adjacency_list[i].size();
        pair<int, int> new_node = pair<int, int>(j, wt);
        if (adjacency_node_size > 0) { // needs to look at correct position to update
            for (int k = 0; k < adjacency_node_size; k++) {
                if (adjacency_list[i][k].first == j) { // updated node
                    adjacency_list[i][k] = new_node;
                    sort(adjacency_list[i].begin(), adjacency_list[i].end()); // optional
                    return;
                }
            }
        }
        adjacency_list[i].push_back(new_node);
        sort(adjacency_list[i].begin(), adjacency_list[i].end()); // optional
        numEdge++;
    }

    // deletes connection at [i][j] 
    void delDirectedEdge(int i, int j) {
        for (int k = 0; k < adjacency_list[i].size(); k++) {
            if (adjacency_list[i][k].first == j) { // finds node at correct index
                adjacency_list[i].erase(adjacency_list[i].begin() + k);
                numEdge--;
            }
        }
    }

    void setEdge(int i, int j, int wt) {
        setDirectedEdge(i, j, wt);
        setDirectedEdge(j, i, wt);
    }

    void delEdge(int i, int j) {
        delDirectedEdge(i, j);
        delDirectedEdge(j, i);
    }

    int n;
private:

    // first: node index, second: edge weight
    vector<vector<pair<int, int>>> adjacency_list;
    int numEdge;
    vector<int> mark;
};

// using tuples to distances min heap structure

struct compare_tuple {
    bool operator()(tuple<int, int, int>& a, tuple<int, int, int>& b) {
        if (get<2>(a) != get<2>(b)) {
            return get<2>(a) > get<2>(b);
        } else if (get<1>(a) != get<1>(b)) {
            return get<1>(a) > get<1>(b);
        } else {
            return get<0>(a) > get<0>(b);
        }
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
            //if (distances_heap.empty()) return;
            auto pv = distances_heap.top(); distances_heap.pop();
            p = get<0>(pv); v = get<1>(pv);
        } while (!Graph.getMark(v) == UNVISITED);
        Graph.setMark(v, VISITED); parent[v] = p;
        int w = Graph.first(v);
        while (w < Graph.n) {
            if (Graph.getMark(w) != VISITED && distance[w] > distance[v] + Graph.weight(v, w)) {
                distance[w] = distance[v] + Graph.weight(v, w);
                distances_heap.push(make_tuple(v, w, distance[w]));
            }
            w = Graph.next(v, w);
        }
    }
}

int main() {
    Graph graph = Graph(5);
    graph.setDirectedEdge(0, 1, 10);
    graph.setDirectedEdge(0, 2, 3);
    graph.setDirectedEdge(0, 3, 20);
    graph.setDirectedEdge(1, 3, 5);
    graph.setDirectedEdge(2, 1, 2);
    graph.setDirectedEdge(2, 4, 15);
    graph.setDirectedEdge(3, 4, 11);

    vector<int> distances(5);
    dijkstra(graph, 0, distances);
    // It is also possible to get the parents vector, for more detailed paths

    for (int i = 0; i < 5; i++) {
        cout << distances[i] << " ";
    }
    cout << endl;

    return 0;
}