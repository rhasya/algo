#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int a, b;
    Edge(int a, int b) : a(a), b(b) {}
};

int find(vector<int> &P, int a) {
    if (P[a] == a) return a;
    return P[a] = find(P, P[a]);
}

void merge(vector<int> &P, int a, int b) {
    int pu = find(P, a);
    int pv = find(P, b);
    if (pu != pv) {
        P[pv] = pu;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int V, E;
    cin >> V >> E;

    vector<vector<int>> D1(E + 1);
    vector<vector<int>> D2(E + 2);
    for (int i = 0; i <= E; i++) {
        D1[i].resize(V + 1);
        D2[i + 1].resize(V + 1);
    }
    for (int i = 1; i <= V; i++) {
        D1[0][i] = i;
        D2[E + 1][i] = i;
    }
    // read Edge
    vector<Edge> edges;
    edges.emplace_back(-1, -1);
    for (int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        edges.emplace_back(a, b);
    }
    
    // make dp
    for (int i = 1; i <= E; i++) {
        for (int j = 1; j <= V; j++) {
            D1[i][j] = D1[i - 1][j];
        }
        merge(D1[i], edges[i].a, edges[i].b);
    }
    for (int i = E; i >= 1; i--) {
        for (int j = 1; j <= V; j++) {
            D2[i][j] = D2[i + 1][j];
        }
        merge(D2[i], edges[i].a, edges[i].b);
    }

    // calculate
    int Q;
    cin >> Q;
    while (Q--) {
        int a, b;
        cin >> a >> b;

        vector<int> &P1 = D1[a - 1];
        vector<int> &P2 = D2[b + 1];
        vector<int> X(V + 1);
        for (int i = 1; i <= V; i++) {
            int pu = find(P1, i);
            int pv = find(P2, i);
            if (pu != pv) {
                if (pu != i && pv != i) {
                    X[pu] = i;
                    X[pv] = i;
                    X[i] = i;
                }
                else if (pu != i) {
                    X[i] = pu;
                }
                else if (pv != i) {
                    X[i] = pv;
                }
            }
            else {
                X[i] = i;
            }
        }
        int cnt = 0;
        for (int i = 1; i <= V; i++) {
            if (i == find(X, i)) {
                cnt++;
            }
        }
        cout << cnt << '\n';
    }
}