#include <iostream>
#include <vector>
using namespace std;

const int MAX_HGT = 18;

vector<vector<int>> G;
vector<vector<int>> P(MAX_HGT);
vector<int> D;

void dfs(int cur, int p, int d) {
    P[0][cur] = p;
    D[cur] = d;
    for (int nx : G[cur]) {
        if (nx != p) {
            dfs(nx, cur, d + 1);
        }
    }
}

int get_lca(int u, int v) {
    // make same depth
    int du = D[u];
    int dv = D[v];
    
    int uu = u;
    int vv = v;

    if (du > dv) {
        int diff = du - dv;
        for (int i = MAX_HGT - 1; i >= 0; i--) {
            if ((diff & (1 << i)) > 0) {
                uu = P[i][uu];
            }
        }
    }
    else if (du < dv) {
        int diff = dv - du;
        for (int i = MAX_HGT - 1; i >= 0; i--) {
            if ((diff & (1 << i)) > 0) {
                vv = P[i][vv];
            }
        }
    }

    if (uu == vv) {
        return uu;
    }
    for (int i = MAX_HGT - 1; i >= 0; i--) {
        if (P[i][uu] != P[i][vv]) {
            uu = P[i][uu];
            vv = P[i][vv];
        }
    }
    return P[0][uu];
}

int main() {
    freopen("./cpp/in", "r", stdin);
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N;
    
    // make graph
    G.resize(N + 1);
    for (int i = 1; i < N; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // find parent
    for (int i = 0; i < MAX_HGT; i++) P[i].resize(N + 1);
    D.resize(N + 1);
    dfs(1, 0, 1);

    // make lca array
    for (int j = 1; j < MAX_HGT; j++) {
        for (int i = 1; i <= N; i++) {
            P[j][i] = P[j - 1][P[j - 1][i]];
        }
    }

    // process query
    cin >> M;
    for (int q = 0; q < M; q++) {
        int r, u, v;
        cin >> r >> u >> v;

        int l0 = get_lca(u, v);
        int d0 = D[u] - D[l0] + D[v] - D[l0];

        int l1 = get_lca(r, u);
        int d1 = D[r] - D[l1] + D[u] - D[l1];
        int l2 = get_lca(r, v);
        int d2 = D[r] - D[l2] + D[v] - D[l2];

        int ans = 0;
        if (d0 == d1 + d2) {
            ans = r;
        }
        else {
            if (l0 == u || l0 == v) {
                if (d1 < d2) ans = l1;
                else ans = l2;
            }
            else {
                
            }
        }
    }
}