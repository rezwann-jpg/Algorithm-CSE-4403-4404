#include <bits/stdc++.h>

using namespace std;

#define fastIO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define INF INT_MAX
const int MAXN = 1e4 + 5;

using ll = long long;

int parent[MAXN];
int height[MAXN];
int V, E;

struct Edge {
    int u;
    int v;
    int weight;
    
    bool operator<(Edge const& e2) {
        return weight < e2.weight;
    }
};

Edge edges[MAXN];

void make_set(int v) {
    parent[v] = v;
    height[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int u, int v) {
    u = find_set(u);
    v = find_set(v);
    
    if (u != v) {
        if (height[u] < height[v])
            swap(u, v);
        parent[v] = u;
        
        if (height[u] == height[v])
            height[u]++;
    }
}

long long kruskal() {
    ll minCost = 0;
    
    for (int i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        ll cost = edges[i].weight;
        
        if (find_set(u) != find_set(v)) {
            minCost += cost;
            union_sets(u, v);
        }
    }
    
    return minCost;
}

int main() {
    fastIO;
    
    cin >> V >> E;
    
    for (int i = 0; i < V; i++) {
        make_set(i);
    }
    
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = { u, v, w };
    }
    
    sort(edges, edges + E);
    cout << kruskal();
    
    return 0;
}
