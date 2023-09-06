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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e5 + 10;
const ll INF = 1e17;
int h[N], e[N], ne[N], w[N], idx;
int now[N], d[N];
int n, m;
ll flow, maxflow;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
bool bfs()
{
    memset(d, 0, sizeof d);
    while(q.size()) q.pop();
    d[1] = 1;
    now[1] = h[1];
    q.push(1);
    while(q.size())
    {
        int u = q.front();
        q.pop();

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(!d[v] && w[i])
            {
                d[v] = d[u] + 1;
                now[v] = h[v];
                q.push(v);
                if(v == n) return true;
            }
        }
    }
    return false;
}

ll dinic(int x, ll flow)
{
    if(x == n) return flow;
    ll rest = flow, k;
    int i;
    for(i = now[x]; i != -1; i = ne[i])
    {
        now[x] = i;
        int v = e[i];
        if(d[v] == d[x] + 1 && w[i])
        {
            k = dinic(v, min((ll)w[i], rest));
            if(!k) d[v] = 0;
            w[i] -= k;
            w[i ^ 1] += k;
            rest -= k;
        }
    }
    return flow - rest;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    m = read(), n = read();
    while(m -- )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
    }

    while(bfs())
        while(flow = dinic(1, INF))
            maxflow += flow;
        
    cout << maxflow << endl;

    return 0;
}
