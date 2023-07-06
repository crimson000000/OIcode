#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e6 + 10;
ll a[N];
vector<int> p[N];
unordered_map<ll, int> mp;
int tot;
int n;
ll ans[N];

void dfs1(int u, int sum, int now)
{
    if(u == n / 2 + 1)
    {
        if(!mp[sum]) mp[sum] = ++ tot;
        p[mp[sum]].push_back(now);
        return;
    }
    dfs1(u + 1, sum + a[u], now | (1 << (u - 1)));
    dfs1(u + 1, sum - a[u], now | (1 << (u - 1)));
    dfs1(u + 1, sum, now);
}

void dfs2(int u, int sum, int now)
{
    if(u == n + 1)
    {
        int t = mp[sum];
        if(t) for(int i = 0; i < p[t].size(); i ++ ) ans[p[t][i] | now] = 1;
        return;
    }
    dfs2(u + 1, sum + a[u], now | (1 << (u - 1)));
    dfs2(u + 1, sum - a[u], now | (1 << (u - 1)));
    dfs2(u + 1, sum, now);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    
    dfs1(1, 0, 0);
    dfs2(n / 2 + 1, 0, 0);

    ll s = 0;
    for(int i = 1; i < (1 << n); i ++ ) s += ans[i];
    cout << s << endl;

    return 0;
}