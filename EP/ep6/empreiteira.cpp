#include <bits/stdc++.h>
using namespace std;

#define VISITED 1
#define UNVISITED 0
#define INFTY INT_MAX
#define EMPTY -1 

class Graph {
public:
    // first: node index, second: edge weight
    Graph(int n) : adjacency_list(n, vector<pair<int, int>>()), mark(n, UNVISITED), numEdge(0), n(n) {}

    int e() { return numEdge; } 

    void setMark(int i, int wt) {
        mark[i] = wt;
    }

    int getMark(int i) {
        return mark[i];
    }

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
        return INFTY;
    }

    int next(int v, int w) {
        for (int i = 0; i < adjacency_list[v].size(); i++) {
            if (adjacency_list[v][i].first == w) {
                if (i + 1 < adjacency_list[v].size()) {
                    return adjacency_list[v][i + 1].first;
                } else {
                    break;
                }
            }
        }
        return n;
    }
    void setDirectedEdge(int i, int j, int wt) {
        if (wt == 0) return; // "error"

        pair<int, int> new_node = pair<int, int>(j, wt);
        adjacency_list[i].push_back(new_node);
        sort(adjacency_list[i].begin(), adjacency_list[i].end()); // optional
        numEdge++;
    }

    void setEdge(int i, int j, int wt) {
        setDirectedEdge(i, j, wt);
        setDirectedEdge(j, i, wt);
    }

    int n;

    // first: node index, second: edge weight
    vector<vector<pair<int, int>>> adjacency_list;
    int numEdge;
    vector<int> mark;
};


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

void prim(Graph& Graph, vector<int>& D, vector<int>& V) {
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, compare_tuple> D_pqueue; // initializes distances min heap
    for (int i = 0; i < Graph.n; i++) {
        D[i] = INFTY; V[i] = EMPTY;
        Graph.setMark(i, UNVISITED);
    }
    D_pqueue.push(make_tuple(0, 0, 0));
    D[0] = 0;
    for (int i = 0; i < Graph.n; i++) {
        int p,v;
        do {
            if (D_pqueue.empty()) return;
            auto pv = D_pqueue.top(); D_pqueue.pop();
            p = get<0>(pv); v = get<1>(pv);
        } while (!Graph.getMark(v) == UNVISITED);

        Graph.setMark(v, VISITED); V[v] = p;

        int w = Graph.first(v);
        while (w < Graph.n) {
            if (Graph.getMark(w) != VISITED && D[w] > Graph.weight(v, w)) {
                D[w] = Graph.weight(v, w);
                D_pqueue.push(make_tuple(v, w, D[w]));
            }
            w = Graph.next(v, w);
        }
    }
}

int main() {
    int cases = 1;
    while (true) {

        int cities, constructions; cin >> cities >> constructions;
        if (cities == 0 && constructions == 0) return 0;

        Graph graph = Graph(cities);
        for (int x = 0; x < constructions; x++) {
            int i, j, p; cin >> i >> j >> p;
            graph.setEdge(i, j, p);
        }
        vector<int> costs(cities, INFTY), cities_v(cities, EMPTY);
        prim(graph, costs, cities_v);
        long total_cost = 0;
        for (int i = 0; i < cities; i++) {
            total_cost += costs[i];
        }
        cout << "Caso " << cases << ": " << total_cost << endl;
        cases++;
    }

    return 0;
}