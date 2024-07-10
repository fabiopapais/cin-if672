#include <bits/stdc++.h>
using namespace std;

#define MAX_RANKING 10000

// modified BFS code
void assign_distances(map<string, set<string>>& graph, map<string, int>& distances) {
    queue<pair<string, int>> visitors_queue; // contains current distance and name of node
    visitors_queue.push({"Ahmad", 0}); distances["Ahmad"] = 0;
    while (visitors_queue.size() > 0) {
        pair<string, int> current_person = visitors_queue.front(); visitors_queue.pop();

        for (string connected_person : graph[current_person.first]) {
            if (distances[connected_person] == MAX_RANKING) {
                distances[connected_person] = current_person.second + 1;
                visitors_queue.push({connected_person, current_person.second + 1});
            }
        }
    }
}

bool compare(pair<string, int>& a, pair<string, int>& b) {
    if (a.second == b.second) {
        return a.first < b.first; // sorts lexicographically if values are equal
    }
    return a.second < b.second; // sorts by value
}

int main() {
    int cases; cin >> cases;
    for (int i = 0; i < cases; i++) {
        map<string, set<string>> graph;
        map<string, int> distances;
        int teams; cin >> teams;
        for (int j = 0; j < teams; j++) {
            string x, y, z; cin >> x >> y >> z;
            // connect all nodes between every one
            graph[x].insert(y);
            graph[x].insert(z);
            graph[y].insert(x);
            graph[y].insert(z);
            graph[z].insert(x);
            graph[z].insert(y);

            // initiate distances map
            distances[x] = MAX_RANKING; distances[y] = MAX_RANKING; distances[z] = MAX_RANKING;
        }

        assign_distances(graph, distances);


        // because you can't sort map: 
        vector<pair<string, int>> sorted_vec(distances.begin(), distances.end());
        sort(sorted_vec.begin(), sorted_vec.end(), compare);

        cout << sorted_vec.size() << endl;
        for (const auto& pair : sorted_vec) {
            if (pair.second == MAX_RANKING) {
                cout << pair.first << " undefined" << endl;
            } else {
                cout << pair.first << " " << pair.second << endl;
            }
        }
    }

    return 0;
}