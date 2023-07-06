#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int h[N], e[N], ne[N], idx;
int hs[N];
int din[N];
int stk[N], top;
bool in_stk[N];
int dfn[N], low[N], tim;
int id[N], w[N], cnt;
int v[N];
int q[N], hh, tt = -1;
int f[N];
int n, m;

void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ top] = u, in_stk[u] = true;
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

    if(dfn[u] == low[u])
    {
        int y;
        cnt ++;
        do {
            y = stk[top -- ];
            in_stk[y] = false;
            id[y] = cnt;
            w[cnt] += v[y];
        } while(y != u);
    }
}

void topsort()
{
    for(int i = 1; i <= cnt; i ++ )
        if(!din[i])
        {
            q[++ tt] = i;
            f[i] = w[i];
        }

    while(hh <= tt)
    {
        int t = q[hh ++ ];
        for(int i = hs[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            din[j] --;
            if(din[j] == 0) q[++ tt ] = j;
        }
    }

    for(int i = 0; i <= tt; i ++ )
    {
        int u = q[i];
        for(int j = hs[u]; j != -1; j = ne[j])
            f[e[j]] = max(f[e[j]], f[u] + w[e[j]]);
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

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) v[i] = read();

    while(m -- )
    {
        int a = read(), b = read();
        add(h, a, b);
    }

    for(int i = 1; i <= n; i ++ )
        if(!dfn[i])
            tarjan(i);

    for(int i = 1; i <= n; i ++ )
        for(int j = h[i]; j != -1; j = ne[j])
        {
            int a = id[i], b = id[e[j]];
            if(a != b)
            {
                din[b] ++;
                add(hs, a, b);
            }
        }

    topsort();

    int ans = 0;
    for(int i = 1; i <= cnt; i ++ )
        ans = max(ans, f[i]);

    cout << ans << endl;
    
    return 0;
}
