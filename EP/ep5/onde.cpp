#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define VISITED 1
#define UNVISITED 0

class Graph {
public:
    Graph(int n): n(n), numEdge(0), mark(n, UNVISITED), pred(n, -1), matrix(n, vector<int>(n, 0)) {}

    int first(int v) {
        for (int i = 0; i < n; i++) {
            if (matrix[v][i] != 0) {
                return i;
            }
        }
        return n;
    }

    int next(int v, int w) {
        for (int i = w + 1; i < n; i++) {
            if (matrix[v][i] != 0) {
                return i;
            }
        }
        return n;
    }

    void setEdge(int i, int j) {
        if (matrix[i][j] == 0) numEdge++;
        matrix[i][j] = 1;
        if (matrix[j][i] == 0) numEdge++;
        matrix[j][i] = 1;
    }

    void BFS(int start, int end) {
        // restart mark
        for (int v = 0; v < n; v++) {
            mark[v] = UNVISITED;
        }
        // restart pred
        for (int v = 0; v < n; v++) {
            pred[v] = -1;
        }
        queue<int> Q; Q.push(start);
        mark[start] = VISITED;
        while (Q.size() > 0) {
            int v = Q.front(); Q.pop();
            int w = first(v);
            while (w < n) {
                if (mark[w] == UNVISITED) {
                    pred[w] = v; // fills predecessor
                    mark[w] = VISITED;
                    Q.push(w);
                }
                w = next(v, w);
            }
        }
    }

    vector<vector<int>> matrix;
    int numEdge;
    int n;
    vector<int> mark;
    vector<int> pred;
};



int main() {
    int cases; cin >> cases;
    for (int k = 1; k <= cases; k++) {
        // fill graph
        int vertices, edges; cin >> vertices >> edges;
        Graph graph = Graph(vertices);
        for (int l = 0; l < edges; l++) {
            int i,j; cin >> i >> j;
            graph.setEdge(i, j);
        }
        // questions
        int questions; cin >> questions;
        cout << "Caso " << k << endl;
        for (int l = 0; l < questions; l++) {
            int s,t; cin >> s >> t;
            if (s == t) {
                cout << s << endl;
                continue;
            }
            graph.BFS(s, t);

            vector<int> path;
            path.push_back(t);
            bool possible = false;
            while (true) {
                path.push_back(graph.pred[t]);
                t = graph.pred[t];
                if (t == s) {
                    possible = true;
                    break;
                } else if (t == -1) {
                    break;
                }
            }

            if (possible) {
                for (int v = path.size() - 1; v >= 1; v--) {
                    cout << path[v] << " ";
                }
                cout << path[0] << endl;
            } else {
                cout << -1 << endl;
            }

        }
    }
    return 0;
}