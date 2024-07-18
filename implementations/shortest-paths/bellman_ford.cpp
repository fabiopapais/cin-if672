#include <bits/stdc++.h>
using namespace std;

#define VISITED 1
#define UNVISITED 0
#define INFTY INT_MAX

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

void bellman_ford(Graph& graph, int s, vector<int>& distance) {
    for (int i = 0; i < graph.n; i++) {
        distance[i] = INFTY;
    }
    distance[s] = 0;
    for (int k = 0; k < graph.n - 1; k++) {
        for (int i = 0; i < graph.n; i++) {
            int j = graph.first(i);
            while (j < graph.n) {
                if (distance[j] > distance[i] + graph.weight(i, j)) {
                    distance[j] = distance[i] + graph.weight(i, j);
                }
                j = graph.next(i, j);
            }
        }
    }
    for (int i = 0; i < graph.n; i++) {
        int j = graph.first(i);
        while (j < graph.n) {
            if (distance[j] > distance[i] + graph.weight(i, j)) {
                // negative cycle detected
                distance[s] = INFTY;
                return;
            }
            j = graph.next(i, j);
        }
    }
}


int main() {
    Graph graph = Graph(5);
    graph.setDirectedEdge(0, 1, -1);
    graph.setDirectedEdge(0, 2, 4);
    graph.setDirectedEdge(1, 2, 3);
    graph.setDirectedEdge(1, 3, 2);
    graph.setDirectedEdge(1, 4, 2);
    graph.setDirectedEdge(3, 2, -5);
    graph.setDirectedEdge(3, 1, 1);
    graph.setDirectedEdge(4, 3, -3);

    vector<int> distances(5);
    bellman_ford(graph, 0, distances);

    for (int i = 0; i < 5; i++) {
        cout << distances[i] << " ";
    }
    cout << endl;
    return 0;
}