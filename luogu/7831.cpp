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
struct edges
{
    int u, v, r, p;
    bool operator < (const edges& a) const
    {
        return r < a.r;
    }
}E[N];
int h[N], e[N], ne[N], idx;
int dout[N];
int ans[N];
int n, m;
queue<int> q;
bitset<N> vis;

inline void add(int a, int cnt)
{
    e[idx] = cnt, ne[idx] = h[a], h[a] = idx ++;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    memset(ans, 0x3f, sizeof ans);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), r = read(), p = read();
        E[i] = {a, b, r, p};
        dout[a] ++;
    }

    sort(E + 1, E + m + 1);
    for(int i = 1; i <= m; i ++ ) add(E[i].v, i);
    for(int i = 1; i <= n; i ++ )
        if(!dout[i])
            q.push(i);
    
    for(int i = m; i; i -- )
    {
        while(q.size())
        {
            int v = q.front();
            q.pop();
            for(int k = h[v]; k != -1; k = ne[k])
            {
                int j = e[k];
                if(vis[j]) continue;
                vis[j] = true;
                int u = E[j].u;
                dout[u] --;
                if(!dout[u]) q.push(u);
                if(ans[v] != INF) ans[u] = min(ans[u], max(E[j].r, ans[v] - E[j].p));
            }
        }
        if(!vis[i])
        {
            vis[i] = true;
            int u = E[i].u;
            dout[u] --;
            if(!dout[u]) q.push(u);
            ans[u] = min(ans[u], E[i].r);
        }
    }

    for(int i = 1; i <= n; i ++ )
        if(ans[i] == 0x3f3f3f3f)
            printf("-1 ");
        else printf("%d ", ans[i]);

    return 0;
}