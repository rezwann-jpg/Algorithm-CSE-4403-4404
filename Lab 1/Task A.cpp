#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(0); cin.tie(0)

void pre() {
    fastio;

    cout << fixed << setprecision(2);
}


int main() {
    pre();
    int l, w, a, b;

    cin >> l >> w >> a >> b;
    float areaRect = l * w;
    float areaTriangle = 0.5 * a * b;
    float areaHalfCircle = 0.5 * 3.14159 * ((a * a + b * b) * 0.25);

    cout << areaRect - (areaTriangle + areaHalfCircle) << "\n";

    return 0;
}