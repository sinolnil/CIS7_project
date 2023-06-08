#include <iostream>
#include <queue>
#include <string>
#include <climits>
#include <vector>

using namespace std;

void search(const vector<vector<int>>& adj, int source, const vector<string>& cities) {
    int V = adj.size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> p_q;

    vector<int> dist(V, INT_MAX);

    p_q.push(make_pair(0, source)); //putting the weight on the top because priority queue should give the nearest node
    dist[source] = 0;

    while (!p_q.empty()) {
        int u = p_q.top().second; //vertex of the nearest node
        p_q.pop();

        for (int v = 0; v < V; ++v) {
            int weight = adj[u][v];

            if (weight > 0 && dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                p_q.push(make_pair(dist[v], v));
            }
        }
    }

    cout << "Shortest Paths from " << cities[source] << ":" << endl;
    for (int k = 0; k < V; ++k) {
        cout << "To " << cities[k] << ": ";
        if (dist[k] == INT_MAX)
            cout << "Not reachable";
        else
            cout << dist[k] ;
        cout << endl;
    }

    int total_cost = 0;
    for (int i = 0; i < V; i++)
        total_cost += 2 * dist[i]; // 2 * dist[i] because he is coming back home

    cout << "Minimum cost will be: " << total_cost << endl;
}

int main() {
    vector<string> cities = {"Riverside", "Moreno Valley", "Perris", "Hemet"};
    vector<vector<int>> adj = {
        {0, 16, 24, 33},
        {16, 0, 18, 26},
        {24, 18, 0, 30},
        {33, 26, 30, 0}
    };

    cout << "Representation of Trips:" << endl;
    for (int i = 0; i < adj.size(); ++i) {
        cout << cities[i] << " -> ";
        for (int j = 0; j < adj[i].size(); ++j) {
            if (adj[i][j] > 0)
                cout << cities[j] << " (" << adj[i][j] << ") ";
        }
        cout << endl;
    }

    cout << endl;

    search(adj, 0, cities); // find the shortest distance from the source node (Riverside)

    return 0;
}

