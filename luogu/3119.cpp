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
int h[N], e[N], ne[N], hs[N], idx;
bool st[N];
int dist[N];
queue<int> q;
int stk[N], tt;
bool in_stk[N];
int low[N], dfn[N], tim;
int id[N], siz[N];
int scc_cnt;
int n, m;

void add(int h[], int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++ tim;
    stk[++ tt] = u;
    in_stk[u] = true;
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
        scc_cnt ++;
        do {
            y = stk[tt -- ];
            in_stk[y] = false;
            id[y] = scc_cnt;
            siz[scc_cnt] ++;
        } while(y != u);
    }
}

void spfa(int u)
{
    q.push(u);
    st[u] = true;
    while(!q.empty())
    {
        int t = q.front();
        q.pop();
        st[t] = false;

        for(int i = hs[t]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] < dist[t] + siz[j])
            {
                dist[j] = dist[t] + siz[j];
                if(!st[j])
                {
                    q.push(j);
                    st[j] = true;
                }
            }
        }
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

    for(int i = 1; i <= scc_cnt; i ++ )
        siz[i + scc_cnt] = siz[i];

    for(int i = 1; i <= n; i ++ )
        for(int j = h[i]; j != -1; j = ne[j])
        {
            int a = id[i], b = id[e[j]];
            if(a != b)
            {
                add(hs, a, b);
                add(hs, a + scc_cnt, b + scc_cnt);
                add(hs, b, a + scc_cnt);
            }
        }
    
    add(hs, id[1], id[1] + scc_cnt);

    spfa(id[1]);

    cout << dist[id[1] + scc_cnt] << endl;
    
    return 0;
}
