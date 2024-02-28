#include<bits/stdc++.h>
using namespace std;
const int INF = INT_MAX;
typedef long long ll;
typedef long double ld;
#define __(); ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

////////////////////////////
//////тест милера рабина
ll mul(ll a, ll b, ll mod) {
    ll res = 0;
    while (b) {
        if (b & 1) res = (res + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }
    return res;
}
ll power(ll a, ll b, ll mod) {
    ll res = 1;
    while (b) {
        if (b & 1)
            res = mul(res, a, mod);
        a = mul(a, a, mod);
        b >>= 1;
    }
    return res;
}
bool check_composite(ll n, ll a, ll d, int s) {
    ll x = power(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; ++r) {
        x = mul(x, x, n);
        if (x == n - 1)
            return false;
    }
    return true;
}
bool miller_rabin(ll n) {
    if (n < 4)
        return (n == 2 || n == 3);
    int s = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    //repeat the miller process untill
    vector <int> v = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 }; //must be true for all the bases
    for (int a : v) {
        if (n == a) return true;
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

/////решето эратосфена
void erat() {
    const ll N = 1047210;
    vector<ll> pr;
    ll lp[N + 1];
    for (ll i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll j = 0; j < (ll)pr.size() && pr[j] <= lp[i] && i * pr[j] <= N; ++j)
            lp[i * pr[j]] = pr[j];
    }
    sort(pr.begin(), pr.end());
}

////////дейkcтра////
int dj() {
    int n, m; cin >> n >> m;
    vector <vector<pair<int, int>>> g(n);
    vector<int> d(n, INF), p(n);
    int s; cin >> s; // стартовая вершина
    int en; cin >> en;//конечная вершина
    s--; en--;
    d[s] = 0;
    vector<char> u(n);
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j)
            if (!u[j] && (v == -1 || d[j] < d[v]))
                v = j;
        if (d[v] == INF)
            break;
        u[v] = true;

        for (size_t j = 0; j < g[v].size(); ++j) {
            int to = g[v][j].first,
                len = g[v][j].second;
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                p[to] = v;
            }
        }
    }

    return d[en];

    /*
    //восстановление пути
    vector<int> path;
    for (int v=t; v!=s; v=p[v])
        path.push_back (v);
    path.push_back (s);
    reverse (path.begin(), path.end());
    */
}



void sparce_table() {
    ////////////////////////////////////////////////
    //--------*** _sparcetable_ ***---------------//
    ////////////////////////////////////////////////
    int n; cin >> n;
    vector<int>a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> Log(n + 1);
    for (int k = 0; (k << 1) <= n; ++k)
        for (int j = (1 << k); j <= min(n, (1 << (k + 1))); ++j)
            Log[j] = k;

    vector<vector<int>>sparce(Log[n] + 1);
    sparce[0] = a;
    for (int k = 0; k <= Log[n]; ++k) {
        for (int i = 0; i + (1 << k) <= n; ++i) {
            sparce[k][i] = max(sparce[k - 1][i], sparce[k - 1][i + (1 << (k - 1))]);
        }
    }

    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        l--; r--;

        int len = r - l + 1;
        int k = Log[len];
        cout << max(sparce[k][l], sparce[k][r - (1 << k) + 1]) << '\n';
    }

}

///dfs///////////////////////////////
vector<int> g[1000];
bool used[1000];
int a[1000];
int dfs(int v)
{
    used[v] = true;
    int mi = a[v];
    for (auto it : g[v])
        if (used[it] != true)
            mi = min(mi, dfs(it));
    return mi;
}

//////////////////////////////

void solve() {
    ////code here
}
signed main() {
    __();
    solve();
}
