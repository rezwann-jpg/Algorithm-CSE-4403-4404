#include <bits/stdc++.h>
using namespace std;

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
}

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    for (int i = 0; i < q; ++i) {
        long long l, r;
        cin >> l >> r;
        auto left_it = std::lower_bound(arr.begin(), arr.end(), l);
        auto right_it = std::upper_bound(arr.begin(), arr.end(), r);
        cout << (right_it - left_it) << "\n";
    }

    return 0;
}
