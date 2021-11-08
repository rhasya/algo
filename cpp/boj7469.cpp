#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int N, Q;
    cin >> N >> Q;
    
    int base = 1;
    while (base <= N) base *= 2;
    vector<vector<int>> tree(base * 2);
    for (int i = 1; i <= N; i++) {
        int a;
        cin >> a;
        tree[base + i].push_back(a);
    }
    for (int i = base - 1; i >= 1; i--) {
        size_t ls = tree[i * 2].size();
        size_t rs = tree[i * 2 + 1].size();
        size_t li = 0;
        size_t ri = 0;
        while (li < ls && ri < rs) {
            if (tree[i * 2][li] < tree[i * 2 + 1][ri]) {
                tree[i].push_back(tree[i * 2][li++]);
            }
            else {
                tree[i].push_back(tree[i * 2 + 1][ri++]);
            }
        }
        while (li < ls) {
            tree[i].push_back(tree[i * 2][li++]);
        }
        while (ri < rs) {
            tree[i].push_back(tree[i * 2 + 1][ri++]);
        }
    }

    auto check = [&tree, base](int l, int r, int v) -> int {
        int left = l + base;
        int right = r + base;
        int ret = 0;
        while (left <= right) {
            if (left % 2 == 1) {
                auto it = lower_bound(tree[left].begin(), tree[left].end(), v);
                ret += (it - tree[left].begin());
            }
            if (right % 2 == 0) {
                auto it = lower_bound(tree[right].begin(), tree[right].end(), v);
                ret += (it - tree[right].begin());
            }
            left = (left + 1) / 2;
            right = (right - 1) / 2;
        }
        return ret;
    };

    for (int q = 0; q < Q; q++) {
        int i, j, k;
        cin >> i >> j >> k;

        // find smaller than mid
        int l = -1e9, r = 1e9;
        while (l < r) {
            int m = (l + r) / 2;
            if (check(i, j, m) < k) {
                l = m + 1;
            }
            else {
                r = m;
            }
        }
        cout << r - 1 << '\n';
    }
}