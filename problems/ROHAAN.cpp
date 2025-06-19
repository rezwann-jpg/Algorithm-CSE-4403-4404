#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define fastIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);

ll dist[51][51];

void floyd_warshall(int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if(dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}

void solve() {
    int n;
    cin >> n;
    
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> dist[r][c];
        }
    }
    
    floyd_warshall(n);
    
    int R;
    cin >> R;
    
    ll ans = 0;
    
    while (R--) {
        int a, b;
        cin >> a >> b;
        
        ans += dist[a - 1][b - 1];
    }
    
    cout << ans;
}

int main() {
    fastIO;
    
    int t;
    cin >> t;
    
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    cout << "\n";
    
    return 0;
}
