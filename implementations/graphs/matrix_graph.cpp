#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define VISITED 1
#define UNVISITED 0

// weighted directed/nondirected graph implementation
class Graph {
public:
    Graph(int n) : matrix(n, vector<int>(n, 0)), mark(n, 0), numEdge(0), n(n) {}

    int e() { return numEdge; }
    
    // returns the first connected node index, if any
    int first(int v) {
        for (int i = 0; i < n; i++) {
            if (matrix[v][i] != 0) return i;
        }
        return n; // if not found, any number higher than n-1 is invalid
    }

    // returns the first connected node index after w, if any
    int next(int v, int w) {
        for (int i = w + 1; i < n; i++) {
            if (matrix[v][i] != 0) return i;
        }
        return n;
    }

    // sets connection with weight wt at [i][j]
    void setDirectedEdge(int i, int j, int wt) {
        if (wt == 0) return; // "error"
        if (matrix[i][j] == 0) numEdge++;
        matrix[i][j] = wt; // always updates weight
    }

    // deletes connection at [i][j] 
    void delDirectedEdge(int i, int j) {
        if (matrix[i][j] != 0) numEdge--;
        matrix[i][j] = 0;
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

    void printMatrix() {
        for (const vector<int> list : matrix) {
            for (const int element : list) {
                cout << element << " ";
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
                    cout << w << " ";
                    Q.push(w);
                }
                w = next(v, w);
            }
            // posVisit(int v);
        }
    }

    vector<vector<int>> matrix;
    int numEdge;
    vector<int> mark;
};

int main() {
    Graph graph = Graph(6);
    graph.setEdge(0, 2, 1);
    // graph.setEdge(0, 4, 1);
    graph.setEdge(2, 3, 1);
    // graph.setEdge(2, 1, 1);
    graph.setEdge(2, 5, 1);
    // graph.setEdge(1, 5, 1);
    graph.setEdge(5, 3, 1);
    // graph.setEdge(5, 4, 1);
    graph.printMatrix();
    cout << endl;
    graph.dfsGraphTraverse();
    graph.bfsGraphTraverse();
    return 0;
}