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
int h[N], e[N], ne[N], idx, hs[N];
int stk[N], top, cnt;
bool in_stk[N];
int low[N], dfn[N], tim;
int din[N], id[N], siz[N];
map<PII, bool> mp;
int n, m;

inline void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++ tim;
    in_stk[u] = true;
    stk[++ top] = u;
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
        int y;
        ++ cnt;
        do {
            y = stk[top -- ];
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
    memset(hs, -1, sizeof hs);

    n = read(), m = read();

    while(m -- )
    {
        int a = read(), b = read();
        add(h, a, b);
    }

    for(int i = 1; i <= n; i ++ )
        if(!dfn[i])
            tarjan(i);

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = h[i]; j != -1; j = ne[j])
        {
            int u = e[j];
            if(id[i] == id[u]) continue;
            if(mp.count({id[i], id[u]})) continue;
            add(hs, id[i], id[u]);
            mp[{id[i], id[u]}] = true;
            din[id[u]] ++;
        }
    }

    int cntt = 0;
    for(int i = 1; i <= cnt; i ++ ) 
        if(!din[i])
            cntt ++;

   
    for(int i = 1; i <= cnt; i ++ )
        if(siz[i] == 1 && !din[i])
        { 
            bool flag = false;
            for(int j = hs[i]; j != -1; j = ne[j])
            {
                int v = e[j];
                if(din[v] == 1) flag = true;
            }
            if(!flag)
            {
                cntt --;
                break;
            }
        }

    printf("%.6lf\n", 1 - (double)cntt / n);

    return 0;
}
