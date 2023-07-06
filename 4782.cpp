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
int dfn[N], low[N], tim;
int stk[N], tt;
bitset<N> in_stk;
int id[N], cnt;
int n, m;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    stk[++ tt] = u, in_stk[u] = true;
    dfn[u] = low[u] = ++ tim;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
        }
        else if(in_stk[j])
            low[u] = min(low[u], dfn[j]);
    }
    
    if(low[u] == dfn[u])
    {
        cnt ++;
        int y;
        do {
            y = stk[tt -- ];
            id[y] = cnt;
            in_stk[y] = false;
        } while(y != u);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int x = read(), p = read(), y = read(), q = read();
        add(x + (1 - p) * n, y + q * n);
        add(y + (1 - q) * n, x + p * n);
    }

    for(int i = 1; i <= n * 2; i ++ )
        if(!dfn[i])
            tarjan(i);

    for(int i = 1; i <= n; i ++ )
        if(id[i] == id[i + n])
        {
            puts("IMPOSSIBLE");
            return 0;
        }

    puts("POSSIBLE");
    for(int i = 1; i <= n; i ++ )
        if(id[i] < id[i + n]) printf("0 ");
        else printf("1 ");

    return 0;
}
