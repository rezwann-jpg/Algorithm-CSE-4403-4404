#include <bits/stdc++.h>
using namespace std;

#define fastIO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using ll = long long;

struct Edge {
    int a;
    int b;
    int cost;
};

int n, m, v;
vector<Edge> edges;
const ll INF = 1e18;

vector<ll> dist;

void bellman_ford() {
    dist.resize(n + 1, INF);
    dist[v] = 0;
    
    for (;;) {
        bool flag = false;
        
        for (auto e : edges) {
            if (dist[e.a] < INF) {
                if (dist[e.b] > dist[e.a] + e.cost) {
                    dist[e.b] = dist[e.a] + e.cost;
                    flag = true;
                }
            }
        }
        
        if (!flag)
            break;
    }
}

void solve() {
    cin >> n >> m;

    while (m--) {
        int a, b, w;
        cin >> a >> b >> w;

        edges.push_back({a, b, w});
    }

    v = 1;
    bellman_ford();

    for (int d = 1; d <= n; d++) {
        if (dist[d] == INF)
            cout << 30000 << " ";
        else
            cout << dist[d] << " ";
    }
}

int main() {
    fastIO;

    solve();

    return 0;
}
