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
int f[N], siz[N], dist[N];
int v[N];
int n;
ll ans;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int fa, int d)
{
    siz[u] = v[u];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dist[j] = dist[u] + v[j];
        dfs(j, u, d + 1);
        siz[u] += siz[j];
    }
    f[1] += v[u] * d;
}

void dfs1(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        f[j] = f[u] + siz[1] - siz[j] - siz[j];
        dfs1(j, u);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();

    for(int i = 1; i <= n; i ++ )
    {
        v[i] = read();
        int a = read(), b = read();
        if(a) add(i, a), add(a, i);
        if(b) add(i, b), add(b, i);
    }

    dfs(1, 1, 0);
    dfs1(1, 1);

    int cnt = 0x3f3f3f3f;
    for(int i = 1; i <= n; i ++ ) cnt = min(cnt, f[i]);

    cout << cnt << endl;

    return 0;
}