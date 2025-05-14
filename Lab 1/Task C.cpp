#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // auto selectionSort = [](vector<int> arr, auto cmp) {
    //     int n = arr.size();
    //     for (int i = 0; i < n - 1; i++) {
    //         int min_idx = i;
    //         for (int j = i + 1; j < n; j++) {
    //             if (cmp(arr[j], arr[min_idx]))
    //                 min_idx = j;
    //         }
    //         swap(arr[i], arr[min_idx]);
    //     }
    //     return arr;
    // };

    // auto bubbleSort = [](vector<int> arr, auto cmp) {
    //     int n = arr.size();
    //     for (int i = 0; i < n - 1; i++) {
    //         for (int j = 0; j < n - i - 1; j++) {
    //             if (!cmp(arr[j], arr[j + 1])) {
    //                 swap(arr[j], arr[j + 1]);
    //             }
    //         }
    //     }
    //     return arr;
    // };

    // auto insertionSort = [](vector<int> arr, auto cmp) {
    //     int n = arr.size();
    //     for (int i = 1; i < n; i++) {
    //         int key = arr[i];
    //         int j = i - 1;
    //         while (j >= 0 && cmp(key, arr[j])) {
    //             arr[j + 1] = arr[j];
    //             j--;
    //         }
    //         arr[j + 1] = key;
    //     }
    //     return arr;
    // };

    // auto cmp_asc = [](int a, int b) { return a < b; };
    // auto cmp_desc = [](int a, int b) { return a > b; };
    // auto cmp_abs = [](int a, int b) {
    //     if (abs(a) != abs(b)) return abs(a) < abs(b);
    //     return a < b;
    // };

    vector<int> asc = a, desc = a, abs_sort = a;
    auto start = high_resolution_clock::now();
    sort(asc.begin(), asc.end());
    sort(desc.begin(), desc.end(), greater<int>());
    sort(abs_sort.begin(), abs_sort.end(), [](int x, int y) {
        if (abs(x) != abs(y)) return abs(x) < abs(y);
        return x < y;
    });
    auto end = high_resolution_clock::now();
    
    for (auto& arr : {asc, desc, abs_sort}) {
        for (int x : arr) cout << x << " ";
        cout << "\n";
    }
    
    // auto start = high_resolution_clock::now();
    // vector<int> sorted1 = insertionSort(a, cmp_asc);
    // vector<int> sorted2 = insertionSort(a, cmp_desc);
    // vector<int> sorted3 = insertionSort(a, cmp_abs);
    // auto end = high_resolution_clock::now();

    // for (int x : sorted1) cout << x << " ";
    // cout << "\n";
    // for (int x : sorted2) cout << x << " ";
    // cout << "\n";
    // for (int x : sorted3) cout << x << " ";
    // cout << "\n";

    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Time taken: " << duration.count() << " ms" << endl;

    return 0;
}
