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

    void setDirectedEdge(int i, int j, int wt) {
        for (int k = 0; k < adjacency_list[i].size(); k++) {
            if (adjacency_list[i][k].first == j && adjacency_list[i][k].first > wt) {
                adjacency_list[i][k].second = wt;
                return;
            }
        }
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

struct compare_tuple {
    bool operator()(tuple<int, int, int>& a, tuple<int, int, int>& b) {
        return get<2>(a) > get<2>(b);
    }
};

void prim(Graph& Graph, vector<int>& D, vector<int>& V) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, compare_tuple> D_heap;
    for (int i = 0; i < Graph.n; i++) {
        D[i] = INFTY; V[i] = EMPTY;
        Graph.setMark(i, UNVISITED);
    }
    D_heap.push(make_tuple(0, 0, 0));
    D[0] = 0;
    for (int i = 0; i < Graph.n; i++) {
        int p,v;
        do {
            if (D_heap.empty()) return;
            auto pv = D_heap.top(); D_heap.pop();
            p = get<0>(pv); v = get<1>(pv);
        } while (!Graph.getMark(v) == UNVISITED);

        Graph.setMark(v, VISITED); V[v] = p;

        for (int j = 0; j < Graph.adjacency_list[v].size(); j++) {
            int w = Graph.adjacency_list[v][j].first;
            int weight = Graph.adjacency_list[v][j].second;
            if (Graph.getMark(w) != VISITED && D[w] > weight) {
                D[w] = weight;
                D_heap.push(make_tuple(v, w, D[w]));
            }
        }
    }
}

int main() {

    while (true) {
        int n, m; cin >> n >> m;
        if (n == 0 && m == 0) return 0;
        Graph graph = Graph(n);
        for (int i = 0; i < m; i++) {
            int a, b, wt; cin >> a >> b >> wt;
            graph.setEdge(a, b, wt);
        }

        vector<int> distances(n), v(n);
        prim(graph, distances, v);

        int biggest_cost = -1;
        for (int i = 1; i < n; i++) {
            if (distances[i] == INFTY) {
                biggest_cost = -1;
                break;
            } else if (distances[i] > biggest_cost) {
                biggest_cost = distances[i];
            }
        }

        if (biggest_cost != -1) {
            cout << biggest_cost << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}