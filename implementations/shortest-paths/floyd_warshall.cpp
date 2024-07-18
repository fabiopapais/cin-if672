#include <bits/stdc++.h>
using namespace std;

#define VISITED 1
#define UNVISITED 0
#define INFTY INT_MAX

// weighted directed/nondirected graph implementation
class Graph {
public:
    Graph(int n) : matrix(n, vector<int>(n, 0)), mark(n, 0), numEdge(0), n(n) {}

    int e() { return numEdge; }

    int weight(int i, int j) {
        return matrix[i][j];
    }
    
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

    vector<vector<int>> matrix;
    int numEdge;
    vector<int> mark;
};

void floyd_warshall(Graph& graph, vector<vector<int>>& distance) {
    for (int i = 0; i < graph.n; i++) {
        for (int j = 0; j < graph.n; j++) {
            if (i == j) distance[i][j] = 0;
            else if (graph.weight(i, j) != 0) distance[i][j] = graph.weight(i, j);
            else distance[i][j] = INFTY;
        }
    }
    for (int k = 0; k < graph.n; k++) {
        for (int i = 0; i < graph.n; i++) {
            for (int j = 0; j < graph.n; j++) {
                if (distance[i][k] != INFTY && distance[k][j] != INFTY && distance[i][j] > distance[i][k] + distance[k][j]) {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
}

int main() {
    Graph graph = Graph(4);
    graph.setDirectedEdge(0, 2, 3);
    graph.setDirectedEdge(1, 0, 2);
    graph.setDirectedEdge(2, 1, 7);
    graph.setDirectedEdge(2, 3, 1);
    graph.setDirectedEdge(3, 0, 6);

    vector<vector<int>> distances(4, vector<int>(4, INFTY));
    floyd_warshall(graph, distances);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << distances[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}