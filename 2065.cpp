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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N], w[N], idx;
int d[N], now[N];
int primes[N * 10], cnt;
map<int, int> mp;
bool st[N * 10];
int n, m, s, t;
int flow, maxflow;

inline void init()
{
    memset(h, -1, sizeof h);
    memset(e, 0, sizeof e);
    memset(ne, 0, sizeof ne);
    memset(w, 0, sizeof w);
    memset(d, 0, sizeof d);
    memset(now, 0, sizeof now);
    idx = 0;
}

inline void init(int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            mp[i] = cnt;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
}

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

inline void build(int id, int x, int op)
{
    for(int i = 1; primes[i] <= x / primes[i]; i ++ )
    {
        if(x % primes[i] == 0)
        {
            if(op == 0) add(id, i + m + n + 1, 1);
            else add(i + m + n + 1, id, 1);
            while(x % primes[i] == 0) x /= primes[i]; 
        }
    }
    if(x > 1) 
    {
        if(op == 0) add(id, mp[x] + m + n + 1, 1);
        else add(mp[x] + n + m + 1, id, 1);
    }
}

queue<int> q;
bool bfs()
{
    while(q.size()) q.pop();
    memset(d, 0, sizeof d);
    q.push(s);
    d[s] = 1;
    now[s] = h[s];
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            now[v] = h[v];
            if(w[i] && !d[v])
            {
                d[v] = d[u] + 1;
                q.push(v);
                if(v == t) return true;
            }
        }
    }
    return false;
}

int dinic(int x, int flow)
{
    if(x == t) return flow;
    int rest = flow, k, i;
    for(i = now[x]; i != -1 && rest; i = ne[i])
    {
        now[x] = i;
        int v = e[i];
        if(w[i] && d[v] == d[x] + 1)
        {
            k = dinic(v, min(rest, w[i]));
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

    int T = read();
    init(10000000);
    while(T -- )
    {
        init();
        n = read(), m = read();
        for(int i = 1; i <= n; i ++ )
        {
            int x = read();
            build(i, x, 0);
        }

        for(int i = 1; i <= m; i ++ )
        {
            int x = read();
            build(i + n, x, 1);
        }

        s = 0, t = N - 2;
        for(int i = 1; i <= n; i ++ ) add(s, i, 1);
        for(int i = 1; i <= m; i ++ ) add(i + n, t, 1);

        while(bfs())
            while(flow = dinic(s, INF))
                maxflow += flow;
        
        cout << maxflow << endl;
        maxflow = 0;
    }
    
    return 0;
}
