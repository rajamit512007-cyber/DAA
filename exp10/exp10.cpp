#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(int V, int E, vector<Edge>& edges, int source) {
    vector<int> dist(V, INT_MAX);

    dist[source] = 0;

    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        bool updated = false;

        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INT_MAX &&
                dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }

        if (!updated)
            break;
    }

    // Check for negative-weight cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INT_MAX &&
            dist[u] + w < dist[v]) {
            cout << "Negative-weight cycle detected!\n";
            return;
        }
    }

    // Print shortest distances
    cout << "\nVertex\tShortest Distance from Source\n";

    for (int i = 0; i < V; i++) {
        cout << i << "\t";

        if (dist[i] == INT_MAX)
            cout << "Unreachable";
        else
            cout << dist[i];

        cout << endl;
    }
}

int main() {
    int V, E;

    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    if (V <= 0 || E < 0) {
        cout << "Invalid graph dimensions.\n";
        return 0;
    }

    vector<Edge> edges(E);

    cout << "Enter edges (source destination weight):\n";

    for (int i = 0; i < E; i++) {
        cin >> edges[i].src
            >> edges[i].dest
            >> edges[i].weight;

        if (edges[i].src < 0 || edges[i].src >= V ||
            edges[i].dest < 0 || edges[i].dest >= V) {
            cout << "Invalid vertex number.\n";
            return 0;
        }
    }

    int source;
    cout << "Enter source vertex (0 to " << V - 1 << "): ";
    cin >> source;

    if (source < 0 || source >= V) {
        cout << "Invalid source vertex.\n";
        return 0;
    }

    bellmanFord(V, E, edges, source);

    return 0;
}