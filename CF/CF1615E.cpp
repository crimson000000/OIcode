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

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
int n, k;
int len[N], dep[N], ln;
int d[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N];
inline void dfs1(int u, int f)
{
    d[u] = d[f] + 1;
    fa[u] = f;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs1(v, u);
        dep[u] = max(dep[u], dep[v]);
    }
    dep[u] ++;
}

inline void dfs2(int u, int t)
{
    if(ne[h[u]] == -1 && u != 1)
    {
        len[++ ln] = d[u] - d[t] + 1;
        return;
    }

    int mx = -1, son;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(dep[v] > dep[u]) continue;
        if(dep[v] > mx)
        {
            mx = dep[v];
            son = v;
        }
    }

    // cout << u << ' ' <<  son << endl;

    dfs2(son, t);

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(dep[v] > dep[u] || v == son) continue;
        dfs2(v, v);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), k = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 1);
    // for(int i = 1; i <= n; i ++ ) cout << dep[i] << ' ';
    dfs2(1, 1);

    if(k >= ln)
    {
        if(k > n / 2 && ln <= n / 2) k = n / 2;
        else if(ln > n / 2) k = ln;
        cout << (ll)k * (n - k) << endl;
    }
    else
    {
        sort(len + 1, len + ln + 1);
        reverse(len + 1, len + ln + 1);
        // for(int i = 1; i <= ln; i ++ ) cout << len[i] << ' ';
        // puts("");
        int nn = n;
        for(int i = 1; i <= k; i ++ )
            nn -= len[i];
        
        if(nn > n / 2) nn = n / 2;
        cout << (ll)k * (n - k) - (ll)nn * (n - nn) << endl;
    }

    return 0;
}
