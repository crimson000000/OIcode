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
int siz[N];
int n;
int ans = 0x3f3f3f3f;
multiset<int> s1, s2;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

inline void dfs1(int u, int fa)
{
    siz[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
    }
}

inline int calc(int a, int b, int c)
{
    return max({abs(a - b), abs(b - c), abs(a - c)});
}

inline void dfs2(int u, int fa)
{
    if(u != 1)
    {
        int out = n - siz[u];
        int x = out / 2;
        if(out > 1)
        {
            auto it = s2.lower_bound(x + siz[u]);
            if(it != s2.end())
                ans = min(ans, calc(siz[u], (*it) - siz[u], n - (*it)));
            
            it = s2.upper_bound(x + siz[u]);
            if(it != s2.begin())
            {
                it --;
                ans = min(ans, calc(siz[u], (*it) - siz[u], n - (*it)));
            }

            it = s1.lower_bound(x);
            if(it != s1.end())
                ans = min(ans, calc(siz[u], *it, n - siz[u] - (*it)));

            it = s1.upper_bound(x);
            if(it != s1.begin())
            {
                it --;
                ans = min(ans, calc(siz[u], *it, n - siz[u] - (*it)));
            }
        }
    }
    if(u != 1) s2.insert(siz[u]);
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs2(v, u);
    }
    s1.insert(siz[u]);
    if(u != 1) s2.erase(s2.find(siz[u]));
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs1(1, 0);
    dfs2(1, 0);

    cout << ans << endl;

    return 0;
} 
