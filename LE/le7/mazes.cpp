#include <bits/stdc++.h>
using namespace std;

#define VISITED 1
#define UNVISITED 0

int spikes = 0;
int resistance = 0;

int can_visit(int x, int y, vector<vector<char>>& maze, vector<vector<int>>& maze_visits) {
    if (x < maze.size() && x >= 0 && y < maze[x].size() && y >= 0 && maze_visits[x][y] == UNVISITED) {
        if (maze[x][y] == 's') return 0;
        else if (maze[x][y] == 'x') return 2;
        else if (maze[x][y] != '#') return 1;
    }
    return -1;
}

bool move_jarmtin(int x, int y, vector<vector<char>>& maze, vector<vector<int>>& maze_visits, vector<int> x_mov, vector<int> y_mov) {
    if (resistance < spikes * 2) return false; 
    // Try all possible paths from (x, y)
    for (int i = 0; i < 4; i++) {
        int next_x = x + x_mov[i];
        int next_y = y + y_mov[i];

        int can_visit_int = can_visit(next_x, next_y, maze, maze_visits);

        if (can_visit_int != -1) {
            maze_visits[next_x][next_y] = VISITED;

            if (can_visit_int == 0) spikes++;
            else if (can_visit_int == 2) return true;

            if (move_jarmtin(next_x, next_y, maze, maze_visits, x_mov, y_mov)) return true;
            // Backtrack
            else maze[next_x][next_y] = UNVISITED;
        }
    }
    return false;
}
   

int main() {
    int n, m; cin >> n >> m >> resistance;
    vector<vector<char>> maze(n, vector<char>(m));
    vector<vector<int>> maze_visits(n, vector<int>(m, UNVISITED));
    pair<int, int> entrance;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char symbol; cin >> symbol;
            if (symbol == '@') entrance = {i, j};
            maze[i][j] = symbol;
        }
    }

    // possible movements (storing outside of recursion)
    vector<int> x_mov = {-1, 1, 0, 0};
    vector<int> y_mov = {0, 0, -1, 1};

    maze_visits[entrance.first][entrance.second] = VISITED;

    bool test = move_jarmtin(entrance.first, entrance.second, maze, maze_visits, x_mov, y_mov);

    if (test) {
        cout << "SUCCESS" << endl;
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}