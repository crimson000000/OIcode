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

const int N = 4e6 + 10, M = 5010;
int h[N], e[N], ne[N], idx;
int dfn[M], low[M], tim;
int stk[M], top;
int cnt;
bool knight[M];
int vis[M];
vector<int> dcc[M];
int color[M];
bool hate[2010][2010];
int n, m, root, now;
bool flag;

void init()
{
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(knight, 0, sizeof knight);
    memset(color, 0, sizeof color);
    memset(dfn, 0, sizeof dfn);
    memset(h, -1, sizeof h);
    memset(hate, 0, sizeof hate);
    memset(low, 0, sizeof low);
    memset(vis, 0, sizeof vis);
    memset(stk, 0, sizeof stk);
    idx = top = tim = 0;
    for(int i = 0; i <= n; i ++ ) dcc[i].clear();
    cnt = 0;
}

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void tarjan(int u)
{
    dfn[u] = low[u] = ++ tim;
    stk[++ top] = u;

    if(u == root && h[u] == -1)
    {
        cnt ++;
        dcc[cnt].push_back(u);
        return;
    }

    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(!dfn[j])
        {
            tarjan(j);
            low[u] = min(low[u], low[j]);
            if(low[j] >= dfn[u])
            {
                cnt ++;
                int y;
                do {
                    y = stk[top -- ];
                    dcc[cnt].push_back(y);
                } while(y != j);
                dcc[cnt].push_back(u);
            }
        }
        else low[u] = min(low[u], dfn[j]);
    }
}

void dfs(int u, int col)
{
    if(vis[u] != now) return;

    color[u] = col;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];

        if(vis[j] != now) continue;
        if(color[j] && color[j] == color[u])
        {
            flag = true;
            return;
        }
        if(!color[j])
            dfs(j, 3 - col);
    }
    return;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    while(cin >> n >> m)
    {
        if(n == 0 && m == 0) break;
        
        init();
        while(m -- )
        {
            int a = read(), b = read();
            if(a == b) continue;
            hate[a][b] = hate[b][a] = true;
        }

        for(int i = 1; i <= n; i ++ )
            for(int j = i + 1; j <= n; j ++ )
            {
                if(!hate[i][j])
                    add(i, j), add(j, i);
            }

        for(root = 1; root <= n; root ++ )
            if(!dfn[root])
                tarjan(root);

        int ans = 0;
        for(int i = 1; i <= cnt; i ++ )
        {
            now = i;
            for(auto u : dcc[i])
                vis[u] = i, color[u] = 0;
            
            flag = false;
            if(dcc[i].size()) dfs(dcc[i][0], 1);

            if(flag)
            {
                for(auto u : dcc[i])
                    knight[u] = true;
            }
        }

        for(int i = 1; i <= n; i ++ )
            if(!knight[i])
                ans ++;

        cout << ans << endl;
    }
    
    return 0;
}
