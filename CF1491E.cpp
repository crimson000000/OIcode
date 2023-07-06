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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], idx;
int fib[N], afib[N << 1];
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int siz[N], maxsiz[N], rt;
bitset<N> vis;
void calc_siz(int u, int fa, int sz)
{
    siz[u] = 1;
    maxsiz[u] = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(vis[i]) continue;
        if(v == fa) continue;
        calc_siz(v, u, sz);
        siz[u] += siz[v];
        maxsiz[u] = max(maxsiz[u], siz[v]);
    }
    maxsiz[u] = max(maxsiz[u], sz - siz[u]);
    if(maxsiz[u] < maxsiz[rt]) rt = u;
}

int a, b, from;
void find(int u, int fa, int fr, int in_fib)
{
    siz[u] = 1;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa || vis[i]) continue;
        find(v, u, i, in_fib);
        siz[u] += siz[v];
    }
    if(siz[u] == fib[in_fib])
    {
        a = u;
        b = e[fr ^ 1];
        from = fr;
    }
}

bool dfz(int u, int in_fib)
{
    if(in_fib == 1 || in_fib == 2) return true; 

    rt = 0;
    maxsiz[rt] = INF;
    calc_siz(u, 0, fib[in_fib]);
    u = rt;

    a = b = from = 0;
    find(u, 0, 0, in_fib - 2);

    if(!a) return false;

    vis[from] = vis[from ^ 1] = true;
    int bb = b;
    
    return (dfz(a, in_fib - 2) && dfz(bb, in_fib - 1));
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();

    fib[0] = fib[1] = 1;
    afib[1] = 1;
    for(int i = 2; i <= 27; i ++ )
    {
        fib[i] = fib[i - 1] + fib[i - 2];
        afib[fib[i]] = i;
    }

    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    if(!afib[n])
    {
        puts("NO");
        return 0;
    }

    if(dfz(1, afib[n])) puts("YES");
    else puts("NO");

    return 0;
}