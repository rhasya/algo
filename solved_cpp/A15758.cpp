#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Query {
    vector<int> v;
    bool bStop;
    Query() : bStop(false) {};
};

vector<int> p;
vector<vector<int>> G;
vector<bool> visit;
int find(int a) {
    if (p[a] == a) return a;
    return p[a] = find(p[a]);
}

bool checkCycle(int now, int tgt) {
    if (now == tgt) return true;
    visit[now] = true;
    for (int nx : G[now]) {
        if (visit[nx]) continue;
        bool tmp = checkCycle(nx, tgt);
        if (tmp) return tmp;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;

    // graph
    G.resize(N + 1);
    vector<int> ind(N + 1, 0);
    // disjoint-set
    p.resize(N + 1);
    for (int i = 0; i <= N; i++) {
        p[i] = i;
    }

    vector<Query> qs;
    for (int q = 0; q < M; q++) {
        int c, a;
        cin >> c;
        Query qu;
        for (int i = 0; i < c; i++) {
            cin >> a;
            qu.v.push_back(a);
        }
        qs.push_back(qu);
    }
    
    for (int q = 0; q < M; q++) {
        Query &qu = qs[q];
        int c = qu.v.size();
        int a = qu.v[0];
        for (int i = 1; i < c; i++) {
            int b = qs[q].v[i];

            // check two vertices are same group
            int pa = find(a);
            int pb = find(b);
            if (pa != pb) {
                G[a].push_back(b);
                p[pb] = pa;
            }
            else {
                // check cycle
                visit.clear();
                visit.resize(N + 1, false);
                bool isCycle = checkCycle(b, a);
                if (isCycle) {
                    qu.bStop = true;
                    goto exit;
                }
                G[a].push_back(b);
            }

            a = b;
        }
    }
    exit:
    for (int i = 0; i <= N; i++) G[i].clear();
    for (int q = 0; q < M; q++) {
        Query &qu = qs[q];
        if (!qu.bStop) {
            int a = qu.v[0], b;
            for (int i = 1; i < (int)qu.v.size(); i++) {
                b = qu.v[i];
                G[a].push_back(b);
                ind[b]++;
                a = b;
            }
        }
        else {
            break;
        }
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= N; i++) {
        if (ind[i] == 0) pq.push(i);
    }
    while (!pq.empty()) {
        int cur = pq.top(); pq.pop();
        cout << cur << ' ';
        for (int nx : G[cur]) {
            ind[nx]--;
            if (ind[nx] == 0) {
                pq.push(nx);
            }
        }
    }
    cout << '\n';
}

