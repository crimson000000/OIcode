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
int h[N], e[N], ne[N], idx;
int hs[N];
int n, m;

inline void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int dfn[N], low[N], tim;
int val[N];
int cnt;
int stk[N], tt;

int num;
void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ tt] = u;
    num ++;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u])
            {
                cnt ++;
                int y;
                // printf("the square point is: %d\n", cnt);
                // printf("it has: ");
                do {
                    y = stk[tt -- ];
                    // printf("%d, ", y);
                    val[y] = -1;
                    val[cnt] ++;
                    add(hs, y, cnt), add(hs, cnt, y);
                } while(y != v);
                // printf("%d\n", u);
                val[cnt] ++;
                add(hs, u, cnt), add(hs, cnt, u);
                val[u] = -1;
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}

int siz[N];
bitset<N> vis;
ll ans;
void dfs(int u, int fa)
{
    vis[u] = true;
    if(u <= n) siz[u] = 1;
    for(int i = hs[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v, u);
        ans += 2ll * siz[u] * siz[v] * val[u];
        siz[u] += siz[v];
    }
    ans += 2ll * val[u] * siz[u] * (num - siz[u]);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);

    n = read(), m = read();
    cnt = n;

    for(int i = 1; i <= m; i ++ ) 
    {
        int a = read(), b = read();
        add(h, a, b), add(h, b, a);
    }

    for(int i = 1; i <= n; i ++ )
        if(!dfn[i])
        {
            num = 0;
            tarjan(i);
            dfs(i, i);
        }

    cout << ans << endl;

    return 0;
}