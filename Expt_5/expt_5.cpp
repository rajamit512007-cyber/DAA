// Amit Raj
// 25/DA/011
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graph {
    int V;                      // Number of vertices
    vector<int> *adj;           // Adjacency list
    vector<int> disc, low;      // Discovery and low-link values
    vector<bool> visited, isAP; // Visited flag and articulation point flag
    int timer;

    void APUtil(int u, int parent) {
        int children = 0;
        visited[u] = true;
        disc[u] = low[u] = ++timer;

        for (int v : adj[u]) {
            if (!visited[v]) {
                children++;
                APUtil(v, u);

              
                low[u] = min(low[u], low[v]);

              
                if (parent == -1 && children > 1)
                    isAP[u] = true;

               
                if (parent != -1 && low[v] >= disc[u])
                    isAP[u] = true;
            }
            else if (v != parent) {
               
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[V];
        disc.assign(V, 0);
        low.assign(V, 0);
        visited.assign(V, false);
        isAP.assign(V, false);
        timer = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void findArticulationPoints() {
        for (int i = 0; i < V; i++) {
            if (!visited[i])
                APUtil(i, -1);
        }

        cout << "\n--- Result ---\n";
        bool found = false;
        cout << "Articulation Points (Cut Vertices) in the graph:\n";
        for (int i = 0; i < V; i++) {
            if (isAP[i]) {
                cout << "Vertex " << i << endl;
                found = true;
            }
        }
        if (!found)
            cout << "No articulation points found in the graph.\n";
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    Graph g(V);
    cout << "Enter each edge as: u v (0-indexed vertices)\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cout << "Edge " << i + 1 << ": ";
        cin >> u >> v;
        g.addEdge(u, v);
    }

    g.findArticulationPoints();

    return 0;
}
