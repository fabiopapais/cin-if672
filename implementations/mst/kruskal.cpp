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

    void printAdjacencyList() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < adjacency_list[i].size(); j++) {
                cout << adjacency_list[i][j].first << ":" << adjacency_list[i][j].second << " ";
            }
            cout << endl;
        }
    }

    int n;
private:

    // first: node index, second: edge weight
    vector<vector<pair<int, int>>> adjacency_list;
    int numEdge;
    vector<int> mark;
};

class DS {
public:
    DS(int size) {
        for (int i = 0; i < size; i++) {
            A[i] = EMPTY;
        }
    }

    int find(int curr) {
        if (A[curr] == EMPTY) return curr;
        A[curr] = find(A[curr]);
        return A[curr];
    }

    void union_set(int a, int b) {
        int root1 = find(a); int root2 = find(b);
        if (root1 != root2) {
            A[root2] = root1;
        }
    }

    unordered_map<int, int> A;
};

struct compare_tuple {
    bool operator()(tuple<int, int, int>& a, tuple<int, int, int>& b) {
        if (get<2>(a) != get<2>(b)) {
            return get<2>(a) > get<2>(b);
        } else if (get<1>(a) != get<1>(b)) {
            return get<1>(a) != get<1>(b);
        } else {
            return get<0>(a) > get<0>(b);
        }
    }
};

void kruskal(Graph& G, Graph& MST) {
    int edgecnt = 1;
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, compare_tuple> edges;

    // initialize edges heap
    for (int i = 0; i < G.n; i++) {
        int w = G.first(i);
        while (w < G.n) {
            edges.push(make_tuple(i, w, G.weight(i, w)));
            w = G.next(i, w);
        }
    }
    DS ds = DS(G.n);
    int numMST = G.n;
    while (numMST > 1) {
        auto vuw = edges.top(); edges.pop();
        int v = get<0>(vuw); int u = get<1>(vuw); int wt = get<2>(vuw);
        if (ds.find(v) != ds.find(u)) {
            ds.union_set(v, u);
            MST.setEdge(v, u, wt);
            numMST--;
        }
    }
}

int main() {
    Graph graph = Graph(5);
    graph.setEdge(0, 1, 10);
    graph.setEdge(0, 2, 3);
    graph.setEdge(0, 3, 20);
    graph.setEdge(1, 3, 5);
    graph.setEdge(2, 1, 2);
    graph.setEdge(2, 4, 15);
    graph.setEdge(3, 4, 11);

    Graph MST = Graph(5);

    kruskal(graph, MST);

    MST.printAdjacencyList(); 

    return 0;
}