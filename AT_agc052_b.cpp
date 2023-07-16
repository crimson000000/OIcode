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
// Tree 1
int h[N], e[N], ne[N], w[N], idx;
// Tree 2
vector<PII> G[N];
unordered_map<int, int> cnt;

int n;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

int dist1[N], dist2[N];
inline void dfs1(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dist1[v] = dist1[u] ^ w[i];
        dfs1(v, u);
    }
}

inline void dfs2(int u, int fa)
{
    for(auto t : G[u])
    {
        int v = t.first, w = t.second;
        if(v == fa) continue;
        dist2[v] = dist2[u] ^ w;
        dfs2(v, u);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read(), c = read(), d = read();
        add(a, b, c), add(b, a, c);
        G[a].emplace_back(b, d);
        G[b].emplace_back(a, d);
    }

    dfs1(1, 1);
    dfs2(1, 1);

    int w1 = 0, w2 = 0;
    for(int i = 1; i <= n; i ++ )
    {
        w1 ^= dist1[i];
        w2 ^= dist2[i];
        cnt[dist1[i]] ++;
    }

    for(int i = 1; i <= n; i ++ )
    {
        dist2[i] ^= (w1 ^ w2);
        if(!cnt[dist2[i]])
        {
            puts("NO");
            return 0;
        }
        cnt[dist2[i]] --;
    }

    puts("YES");

    return 0;
}
