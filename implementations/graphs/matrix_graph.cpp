#include <iostream>
#include <vector>
#include <queue>
#include <stack>
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

    // must remeber to delete stack pointer
    stack<int>* toposort(int v) {
        stack<int>* sorted = new stack<int>();
        toposorthelp(v, sorted);
        return sorted;
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

    vector<vector<int>> matrix;
    int numEdge;
    vector<int> mark;
};

int main() {
    Graph graph = Graph(7);
    graph.setDirectedEdge(0, 2, 1);
    graph.setDirectedEdge(0, 1, 1);
    graph.setDirectedEdge(1, 5, 1);
    graph.setDirectedEdge(1, 3, 1);
    graph.setDirectedEdge(1, 4, 1);
    graph.setDirectedEdge(2, 3, 1);
    graph.setDirectedEdge(3, 4, 1);
    graph.setDirectedEdge(4, 6, 1);
    graph.printMatrix();
    cout << endl;
    stack<int>* sorted = graph.toposort(0);
    while (!sorted->empty()) {
        cout << sorted->top() << " ";
        sorted->pop();
    }
    delete[] sorted;
    return 0;
}