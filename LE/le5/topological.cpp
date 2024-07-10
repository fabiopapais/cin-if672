#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class Graph {
public:
    Graph(int n) : matrix(n, vector<int>(n, 0)), mark(n, 0), numEdge(0), n(n), dep(n, 0) {}
    
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
        dep[j] += 1; // updates dependency vector
    }

    // deletes connection at [i][j] 
    void delDirectedEdge(int i, int j) {
        if (matrix[i][j] != 0) numEdge--;
        matrix[i][j] = 0;
        dep[j] -= 1;
    }


    // Kahns Algorithm 
    vector<int>* toposort(int v) {
        vector<int>* sorted = new vector<int>();
        priority_queue<int, vector<int>, greater<int>> no_deps;
        for (int i = 0; i < n; i++) {
            if (dep[i] == 0) {
                no_deps.push(i);
            }
        }
        while (no_deps.size() > 0) {
            int current = no_deps.top(); no_deps.pop();
            sorted->push_back(current);
            int m = first(current);
            while (m < n) {
                delDirectedEdge(current, m);
                if (dep[m] == 0) {
                    no_deps.push(m);
                }
                m = next(current, m);
            }
        }
        if (numEdge > 0) { // error (graph has cycle)
            sorted->clear();
        }
        return sorted;
    }

    int n;
    vector<int> dep;
private:
    vector<vector<int>> matrix;
    int numEdge;
    vector<int> mark;
};

int main() {
    int n, m; cin >> n >> m;
    Graph graph = Graph(n);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        graph.setDirectedEdge(x - 1, y - 1, 1);
    }

    vector<int>* sorted = graph.toposort(0);
    if (sorted->size() == n) {
        for (int i = 0; i < n; i++) {
            cout << (*sorted)[i] + 1 << " ";
        }
        cout << endl;
    } else {
        cout << "Sandro fails." << endl;
    }
}