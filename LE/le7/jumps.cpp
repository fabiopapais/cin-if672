#include <bits/stdc++.h>
using namespace std;

#define EMPTY -1
#define VISITED 1
#define UNVISITED 0

bool can_visit(int x, int y, vector<vector<int>>& board) {
    return x >= 0 && x < board.size() && y >= 0 && y < board[x].size() && board[x][y] == UNVISITED;
}

// helsp maximizing path lenght
void update_max_path(int current_count, int &max_count, vector<vector<int>> &best_board, const vector<vector<int>> &board) {
    if (current_count > max_count) {
        max_count = current_count;
        best_board = board;
    }
}

bool move_knight(int x, int y, int total_cells, int current_count, vector<vector<int>>& board, vector<int> x_mov, vector<int> y_mov, int &max_count, vector<vector<int>> &best_board) {
    // Update the maximum path length
    update_max_path(current_count, max_count, best_board, board);
    
    // Try all possible paths from (x, y)
    for (int i = 0; i < 8; i++) {
        int next_x = x + x_mov[i];
        int next_y = y + y_mov[i];

        if (can_visit(next_x, next_y, board)) {
            board[next_x][next_y] = VISITED;
            if (move_knight(next_x, next_y, total_cells, current_count + 1, board, x_mov, y_mov, max_count, best_board)) return true;
            // Backtrack
            board[next_x][next_y] = UNVISITED;
        }
    }
    return false;
}

int main() {
    int cases = 1;
    while (true) {
        int n; cin >> n;
        if (n == 0) return 0;

        // Load matrix
        pair<int, int> beginning;
        int total_cells = 0;
        vector<vector<int>> board(n);

        for (int i = 0; i < n; i++) {
            int skip, num_cells; cin >> skip >> num_cells;
            if (i == 0) beginning = make_pair(0, skip);

            board[i].resize(skip + num_cells, EMPTY);
            for (int j = skip; j < skip + num_cells; j++) {
                board[i][j] = UNVISITED;
                total_cells++;
            }
        }

        // Knight movements (storing outside of recursion)
        vector<int> x_mov = {-2, -2, -1, -1, 1, 1, 2, 2};
        vector<int> y_mov = {-1, 1, -2, 2, -2, 2, -1, 1};

        board[beginning.first][beginning.second] = VISITED;

        int max_count = 0;
        vector<vector<int>> best_board = board;

        // Fills solution
        move_knight(beginning.first, beginning.second, total_cells, 1, board, x_mov, y_mov, max_count, best_board);

        int unvisited_cells = 0;        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < best_board[i].size(); j++) {
                if (best_board[i][j] == UNVISITED) unvisited_cells++;
            } 
        }

        cout << "Case " << cases << ", " << unvisited_cells;
        if (unvisited_cells == 1) {
            cout << " square can not be reached.";
        } else {
            cout << " squares can not be reached.";
        }
        cout << endl;

        cases += 1;
    }

    return 0;
}
