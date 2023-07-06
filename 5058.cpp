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

const int N = 3e6 + 10;
int h[N], e[N], ne[N], idx;
int hs[N];
int n, s, t;

int dfn[N], low[N], tim;
int stk[N], tt;
int cnt;

inline void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    stk[++ tt] = u;
    dfn[u] = low[u] = ++ tim;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u])
            {
                int y;
                cnt ++;
                do {
                    y = stk[tt -- ];
                    add(hs, cnt, y), add(hs, y, cnt);
                } while(y != v);
                add(hs, cnt, u), add(hs, u, cnt);
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

int fa[N], dep[N];
void dfs(int u, int f)
{
    dep[u] = dep[f] + 1;
    fa[u] = f;
    for(int i = hs[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == f) continue;
        dfs(v, u);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    n = read();
    while(1)
    {
        int a = read(), b = read();
        if(a == 0 && b == 0) break;
        add(h, a, b), add(h, b, a);
    }

    cnt = n;

    s = read(), t = read();

    for(int i = 1; i <= n; i ++ )
        if(!dfn[i])
            tarjan(i);

    dfs(s, 0);

    t = fa[t];
    int ans = 0x3f3f3f3f;
    while(t != s)
    {
        if(t <= n) ans = min(ans, t);
        t = fa[t];
    }

    if(ans == 0x3f3f3f3f) puts("No solution");
    else cout << ans << endl;

    return 0;
}