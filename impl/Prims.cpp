#include <bits/stdc++.h>

using namespace std;

#define fastIO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define INF INT_MAX
const int MAXN = 1e4 + 5;

using ll = long long;
using pli = pair<ll, int>;
bool marked[MAXN];
vector<pli> adj[MAXN];

ll PRIM(int root) {
    priority_queue<pli, vector<pli>, greater<pli>> Q;
    ll minCost = 0;
    Q.push({0, root});
    
    while (!Q.empty()) {
        pli p = Q.top();
        Q.pop();
        
        int u = p.second;
        
        if (marked[u])
            continue;
            
        minCost += p.first;
        marked[u] = true;
        
        for (int i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].second;
            if (marked[v] == false)
                Q.push(adj[u][i]);
        }
    }
    
    return minCost;
}

int main() {
    fastIO;
  
    int V, E;
    cin >> V >> E;

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    int root = 1;
    // cin >> root;

    cout << PRIM(root);

    return 0;
}
