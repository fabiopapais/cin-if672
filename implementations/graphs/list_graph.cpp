#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

#define VISITED 1
#define UNVISITED 0

// directed/nondirected graph implementation
class Graph {
public:
    // first: node index, second: edge weight
    Graph(int n) : adjacency_list(n, vector<pair<int, int>>()), mark(n, UNVISITED), numEdge(0), n(n) {}

    int e() { return numEdge; }
    
    // returns the first connected node index, if any
    int first(int v) {
        if (adjacency_list[v].size() > 0) {
            return adjacency_list[v][0].first;
        }
        return n;
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

    void dfsGraphTraverse() {
        for (int v = 0; v < n; v++) {
            mark[v] = UNVISITED;
        }
        
        for (int v = 0; v < n; v++) { // assures searching into unconnected nodes
            if (mark[v] == UNVISITED) {
                DFS(v);
            }
        }
        cout << endl;
    }

    void bfsGraphTraverse() {
        for (int v = 0; v < n; v++) {
            mark[v] = UNVISITED;
        }
        for (int v = 0; v < n; v++) { // assures searching into unconnected nodes
            if (mark[v] == UNVISITED) {
                BFS(v);
            }
        }
        cout << endl;
    }

    // must remeber to delete stack pointer
    stack<int>* toposort(int v) {
        stack<int>* sorted = new stack<int>();
        toposorthelp(v, sorted);
        return sorted;
    }

    void printAdjacencyList() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < adjacency_list[i].size(); j++) {
                cout << adjacency_list[i][j].first << " ";
            }
            cout << endl;
        }
    }

    int n;
private:

    void DFS(int v) {
        // preVisit(int v);
        mark[v] = VISITED;
        cout << v << " ";
        int w = first(v);
        while (w < n) {
            if (mark[w] == UNVISITED) DFS(w);
            w = next(v, w);
        }
        // posVisit(int v);
    }

    void BFS(int start) {
        queue<int> Q;
        Q.push(start);
        cout << start << " ";
        mark[start] = VISITED;
        while (Q.size() > 0) {
            int v = Q.front(); Q.pop();
            // preVisit(int v);
            int w = first(v);
            while (w < n) {
                if (mark[w] == UNVISITED) {
                    mark[w] = VISITED;
                    cout << w << " "; // "visit" code goes here
                    Q.push(w);
                }
                w = next(v, w);
            }
            // posVisit(int v);
        }
    }

    void toposorthelp(int v, stack<int>* s) {
        mark[v] = VISITED;
        int w = first(v);
        while (w < n) {
            if (mark[w] == UNVISITED) {
                toposorthelp(w, s);
            }
            w = next(v, w);
        }
        s->push(v);
    }

    // first: node index, second: edge weight
    vector<vector<pair<int, int>>> adjacency_list;
    int numEdge;
    vector<int> mark;
};

int main() {
    /*
    Graph graph = Graph(6);
    graph.setEdge(0, 4, 1);
    graph.setEdge(0, 2, 1);
    graph.setEdge(2, 3, 1);
    graph.setEdge(2, 1, 1);
    graph.setEdge(2, 5, 1);
    graph.setEdge(1, 5, 1);
    graph.setEdge(5, 3, 1);
    graph.setEdge(5, 4, 1);
    graph.printAdjacencyList();
    graph.dfsGraphTraverse();
    graph.bfsGraphTraverse();
    */
    Graph graph = Graph(6);
    graph.setEdge(0, 2, 1);
    graph.setEdge(0, 4, 1);
    graph.setEdge(2, 3, 1);
    graph.setEdge(2, 1, 1);
    graph.setEdge(2, 5, 1);
    graph.setEdge(1, 5, 1);
    graph.setEdge(3, 5, 1);
    graph.setEdge(4, 5, 1);
    graph.printAdjacencyList();
    graph.dfsGraphTraverse();
    
    return 0;
}