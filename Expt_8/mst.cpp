// Minimum Spanning Tree using Prim's and Kruskal's algorithms
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

// ---------- Disjoint Set Union (for Kruskal) ----------
class DSU {
    vector<int> parent, rnk;
public:
    DSU(int n) : parent(n), rnk(n, 0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;           // would form a cycle
        if (rnk[a] < rnk[b]) swap(a, b);
        parent[b] = a;
        if (rnk[a] == rnk[b]) rnk[a]++;
        return true;
    }
};

// ---------- Kruskal's Algorithm: O(E log E) ----------
pair<int, vector<Edge>> kruskal(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(),
         [](const Edge &a, const Edge &b) { return a.w < b.w; });
    DSU dsu(n);
    vector<Edge> mst;
    int total = 0;
    for (const Edge &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            total += e.w;
            if ((int)mst.size() == n - 1) break;
        }
    }
    return {total, mst};
}

// ---------- Prim's Algorithm (min-heap): O(E log V) ----------
pair<int, vector<Edge>> prim(int n, const vector<vector<pair<int, int>>> &adj, int start = 0) {
    vector<bool> inMST(n, false);
    vector<Edge> mst;
    int total = 0;
    // (weight, vertex, parent)
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.push({0, start, -1});
    while (!pq.empty() && (int)mst.size() < n - 1) {
        auto [w, u, p] = pq.top();
        pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true;
        if (p != -1) {
            mst.push_back({p, u, w});
            total += w;
        }
        for (auto [v, wt] : adj[u])
            if (!inMST[v]) pq.push({wt, v, u});
    }
    return {total, mst};
}

void printMST(const string &name, const pair<int, vector<Edge>> &res) {
    cout << "=== " << name << " ===\n";
    cout << left << setw(10) << "Edge" << "Weight\n";
    cout << "-------------------\n";
    for (const Edge &e : res.second)
        cout << left << setw(10) << (to_string(e.u) + " - " + to_string(e.v)) << e.w << "\n";
    cout << "-------------------\n";
    cout << "Total MST weight = " << res.first << "\n\n";
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<Edge> edges(m);
    vector<vector<pair<int, int>>> adj(n);
    cout << "Enter each edge as: u v weight (0-indexed)\n";
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        adj[edges[i].u].push_back({edges[i].v, edges[i].w});
        adj[edges[i].v].push_back({edges[i].u, edges[i].w});
    }
    cout << "\n";

    auto k = kruskal(n, edges);
    auto p = prim(n, adj);

    if ((int)k.second.size() != n - 1) {
        cout << "Graph is disconnected: no spanning tree exists.\n";
        return 0;
    }

    printMST("Kruskal's Algorithm", k);
    printMST("Prim's Algorithm (start = 0)", p);

    cout << (k.first == p.first ? "Both algorithms give the same MST weight.\n"
                                : "Mismatch in MST weights!\n");
    return 0;
}
