#ifndef AOI_ALGOS_H
#define AOI_ALGOS_H

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define all(x) x.begin(), x.end()
#define pb push_back
#define endl '\n'

const int INF = 1e18;
const int MOD = 1e9 + 7;
const int N = 2e5 + 5;

// GCD, LCM, modpow
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int lcm(int a, int b) { return a / gcd(a, b) * b; }
int modpow(int a, int b, int m = MOD) {
    int res = 1; a %= m;
    while (b > 0) {
        if (b & 1) res = res * a % m;
        a = a * a % m; b >>= 1;
    }
    return res;
}

// Sieve
vector<int> prime;
bitset<N> is_prime;
void sieve(int n = N - 1) {
    is_prime.set();
    is_prime[0] = is_prime[1] = 0;
    for (int i = 2; i <= n; ++i)
        if (is_prime[i]) {
            prime.pb(i);
            for (int j = i * i; j <= n; j += i) is_prime[j] = 0;
        }
}

// Binary Search
int binary_search(vector<int>& a, int x) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (a[m] == x) return m;
        else if (a[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

// Graph: DFS/BFS
vector<int> adj[N];
bool visited[N];
void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) if (!visited[v]) dfs(v);
}
void bfs(int start) {
    queue<int> q; q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) if (!visited[v]) {
            visited[v] = true;
            q.push(v);
        }
    }
}

// Dijkstra
vector<pair<int, int>> g[N];
vector<int> dijkstra(int s, int n) {
    vector<int> dist(n + 1, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    dist[s] = 0; pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// DSU
int par[N], sz[N];
void dsu_init(int n) {
    for (int i = 1; i <= n; i++) par[i] = i, sz[i] = 1;
}
int find(int x) {
    return (par[x] == x ? x : par[x] = find(par[x]));
}
void unite(int a, int b) {
    a = find(a), b = find(b);
    if (a != b) {
        if (sz[a] < sz[b]) swap(a, b);
        par[b] = a; sz[a] += sz[b];
    }
}

// Segment Tree
int seg[4 * N];
void build(int id, int l, int r, vector<int>& a) {
    if (l == r) { seg[id] = a[l]; return; }
    int m = (l + r) / 2;
    build(id*2, l, m, a); build(id*2+1, m+1, r, a);
    seg[id] = seg[id*2] + seg[id*2+1];
}
int query(int id, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 0;
    if (ql <= l && r <= qr) return seg[id];
    int m = (l + r) / 2;
    return query(id*2, l, m, ql, qr) + query(id*2+1, m+1, r, ql, qr);
}
void update(int id, int l, int r, int pos, int val) {
    if (l == r) { seg[id] = val; return; }
    int m = (l + r) / 2;
    if (pos <= m) update(id*2, l, m, pos, val);
    else update(id*2+1, m+1, r, pos, val);
    seg[id] = seg[id*2] + seg[id*2+1];
}

// Fenwick Tree (BIT)
int bit[N];
void bit_update(int i, int val) {
    for (; i < N; i += i & -i) bit[i] += val;
}
int bit_query(int i) {
    int res = 0;
    for (; i > 0; i -= i & -i) res += bit[i];
    return res;
}

#endif
