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
const ll INF = 1e17;
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int n, m, s, t;
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
    q.push(s);
    now[s] = h[s];
    d[s] = 1;
    while(q.size())
    {
        int v = q.front();
        q.pop();

        for(int i = h[v]; i != -1; i = ne[i])
        {
            if(!w[i]) continue;
            int j = e[i];
            if(!d[j])
            {
                now[j] = h[j];
                d[j] = d[v] + 1;
                q.push(j);
                if(j == t) return true;
            }
        }
    }
    return false;
}

ll dinic(int u, ll flow)
{
    if(u == t) return flow;
    ll rest = flow;
    int k, i;
    for(i = now[u]; i != -1 && rest; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(w[i] && d[v] == d[u] + 1)
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

    n = read(), m = read(), s = read(), t = read();
    while(m -- )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
    }

    while(bfs())
        while(flow = dinic(s, INF))
            maxflow += flow;

    cout << maxflow << endl;
    
    return 0;
}
