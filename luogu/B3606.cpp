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

const int N = 5010, INF = 0x3f3f3f3f;
int h[N], e[N], ne[N];
ll w[N], idx;
int now[N], d[N];
queue<int> q;
int n, m, s, t;
ll mx;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

bool bfs()
{
    memset(d, 0, sizeof d);
    while(!q.empty()) q.pop();
    q.push(s);
    d[s] = 1;
    now[s] = h[s];
    while(q.size())
    {
        int x = q.front();
        q.pop();
        for(int i = h[x]; i != -1; i = ne[i])
        {
            int ver = e[i];
            if(w[i] && !d[ver])
            {
                q.push(ver);
                now[ver] = h[ver];
                d[ver] = d[x] + 1;
                if(ver == t) return true;
            }
        }
    }
    return false;
}

int dinic(int x, ll flow)
{
    if(x == t) return flow;
    ll rest = flow;
    for(int i = now[x]; i != -1 && rest; i = ne[i])
    {
        now[x] = i;
        int j = e[i];
        if(w[i] && d[j] == d[x] + 1)
        {
            int k = dinic(j, min(w[i], rest));
            if(!k) d[j] = 0;
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

    for(int i = 0; i < m; i ++ )
    {
        int a = read(), b = read(), c = read();
        add(a, b, c);
    }

    ll flow = 0;
    while(bfs()) 
    {
        while(flow = dinic(s, INF))
            mx += flow;
    }

    cout << mx << endl;

    return 0;
}
