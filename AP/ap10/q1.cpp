#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define VISITED 1
#define UNVISITED 0

class Graph {
public:
    Graph(int n): mark(n, UNVISITED), matrix(n, vector<int>(n, 0)), n(n), numEdge(0) {}

    int first(int v) {
        for (int i = 0; i < n; i++) {
            if (matrix[v][i] != 0) return i;
        }
        return n;
    }

    int next(int v, int w) {
        for (int i = w + 1; i < n; i++) {
            if (matrix[v][i] != 0) return i;
        }
        return n;
    }

    void setEdge(int i, int j) {
        if (matrix[i][j] == 0) numEdge++;
        matrix[i][j] = 1;
        if (matrix[j][i] == 0) numEdge++;
        matrix[j][i] = 1;
    }

    void printMatrix() {
        for (const vector<int> list : matrix) {
            for (const int element : list) {
                cout << element << " ";
            }
            cout << endl;
        }
    }

    void delEdge(int i, int j) {
        if (matrix[i][j] != 0) numEdge--;
        matrix[i][j] = 0;
        if (matrix[j][i] != 0) numEdge--;
        matrix[j][i] = 0;
    }

    void dfsGraphTraverse(int start) {
        for (int v = 0; v < n; v++) {
            setMark(v, UNVISITED);
        }
        for (int v = start; v < n + start; v++) {
            int vc = v % n;
            if (getMark(vc) == UNVISITED) {
                DFS(vc);
            }
        }
        cout << endl;
    }

    void bfsGraphTraverse(int start) {
        for (int v = 0; v < n; v++) {
            setMark(v, UNVISITED);
        }
        for (int v = start; v < n + start; v++) {
            int vc = v % n;
            if (getMark(vc) == UNVISITED) {
                BFS(vc);
            }
        }
        cout << endl;
    }

private:
    void setMark(int v, int value) { mark[v] = value; }
    int getMark(int v) { return mark[v]; }

    void DFS(int v) {
        // pre
        setMark(v, VISITED);
        cout << v << " ";
        int w = first(v);
        while (w < n) {
            if (getMark(w) == UNVISITED) DFS(w);
            w = next(v, w);
        }
        // pos
    }

    void BFS(int start) {
        queue<int> Q;
        Q.push(start);
        setMark(start, VISITED);
        cout << start << " ";
        while (Q.size() > 0) {
            int v = Q.front(); Q.pop();
            // pre
            int w = first(v);
            while (w < n) {
                if (getMark(w) == UNVISITED) {
                    setMark(w, VISITED);
                    cout << w << " ";
                    Q.push(w);
                }
                w = next(v, w);
            }
            // pos
        } 
    }

    vector<vector<int>> matrix;
    int n;
    int numEdge;
    vector<int> mark;
};

int main() {
    int n, operations; cin >> n; cin >> operations;
    Graph graph = Graph(n);
    for (int i = 0; i < operations; i++) {
        string command; cin >> command;
        if (command == "add") {
            int v1, v2; cin >> v1; cin >> v2;
            graph.setEdge(v1, v2);
        } else if (command == "BFS") {
            int v1; cin >> v1;
            graph.bfsGraphTraverse(v1);
        } else if (command == "DFS") {
            int v1; cin >> v1;
            graph.dfsGraphTraverse(v1);
        }
    }
    return 0;
}