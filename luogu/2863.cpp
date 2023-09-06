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

const int N = 1e6 +10;
int h[N], e[N], ne[N], idx;
int dfn[N], low[N], tim;
int stk[N], tt;
bool in_stk[N];
int siz[N], id[N], cnt;
int n, m, ans;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ tt] = u, in_stk[u] = true;
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
            y = stk[tt --];
            in_stk[y] = false;
            id[y] = cnt;
            siz[cnt] ++;
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

    while(m -- )
    {
        int a = read(), b = read();
        add(a, b);
    }

    for(int i = 1; i <= n; i ++ )
        if(!dfn[i])
            tarjan(i);

    for(int i = 1; i <= cnt; i ++ )
        if(siz[i] > 1)
            ans ++;

    cout << ans << endl;
    
    return 0;
}
