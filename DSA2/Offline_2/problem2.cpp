#include <bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
#define vll vector<ll>
#define vllp vector<pair<ll, ll>>
#define endl '\n'
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define vin(x) for (auto &i : x) cin >> i;
#define vout(x) for (auto &i : x) cout << i << " ";
#define all(x) x.begin(), x.end()
#define forn(i, n) for(int i = 0; i < (n); i++)
const int MOD = 1e9 + 7;
const ll INF = 1e18;

void solve() {
    int n, m;
    cin >> n;
    unordered_map<string, int> currencyIndex;
    forn(i, n) {
        string currency;
        cin >> currency;
        currencyIndex[currency] = i + 1;
    }
    cin >> m;
    vector <tuple<int, int, double>> edges(n + 1);

    forn(i, m) {
        string u, v;
        double rate;
        cin >> u >> rate >> v;
        int u_node = currencyIndex[u];
        int v_node = currencyIndex[v];
        edges.push_back({u_node, v_node, -log(rate)});
        
    }

    vector <double> dist(n + 1, 0.0);;
    
    for(int i = 0; i < n - 1; i++) {
        for(auto [u, v, w] : edges) {
            if(dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
            }
        }
    }
    for (auto [u, v, w] : edges) {
        if (dist[v] > dist[u] + w) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}

signed main() {
    fastIO();
    int tt = 1;
    // cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}