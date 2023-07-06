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

const int N = 1e5 + 10, INF = 2147483647;
int h[N], e[N], ne[N], w[N], idx;
int dep[N], flow[N], gap[N];
int n, m, s, t;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, ne[idx] = h[b], h[b] = idx ++;
}

bool is_in[N], is[N];
bool bfs()
{
    for(int i = 1; i <= n; i ++ ) dep[i] = INF;
    dep[t] = 0;
    queue<int> q;
    q.push(t);
    is[t] = true;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        is[u] = false;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(w[i] || dep[v] <= dep[u] + 1) continue;
            dep[v] = dep[u] + 1;
            if(!is[v])
            {
                q.push(v);
                is[v] = true;
            }
        }
    }
    return dep[s] == INF;
}

struct cmp
{
    bool operator () (int a, int b) const
    {
        return dep[a] < dep[b];
    }
};

priority_queue<int, vector<int>, cmp> q;
inline void push(int u)
{
    int nowflow = 0;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(!w[i] || dep[u] != dep[v] + 1) continue;
        nowflow = min(flow[u], w[i]);
        w[i] -= nowflow;
        w[i ^ 1] += nowflow;
        flow[u] -= nowflow;
        flow[v] += nowflow;
        if(!is_in[v] && v != t && v != s)
        {
            q.push(v);
            is_in[v] = true;
        }
        if(!flow[u]) break;
    }
}

inline void relabel(int u)
{
    dep[u] = INF;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        if(!w[i]) continue;
        int v = e[i];
        dep[u] = min(dep[u], dep[v] + 1);
    }
}

int maxflow()
{
    if(bfs()) return 0;
    dep[s] = n;
    
    for(int i = 1; i <= n; i ++ )
        if(dep[i] < INF)
            gap[dep[i]] ++;
    
    for(int i = h[s]; i != -1; i = ne[i])
    {
        int v = e[i];
        int nowflow = w[i];
        if(nowflow)
        {
            flow[s] -= nowflow;
            flow[v] += nowflow;
            w[i] -= nowflow;
            w[i ^ 1] += nowflow;
            if(v != t && v != s && !is_in[v])
            {
                q.push(v);
                is_in[v] = true;
            }
        }
    }

    while(q.size())
    {
        int u = q.top();
        q.pop();
        is_in[u] = false;
        push(u);
        if(flow[u])
        {
            gap[dep[u]] --;
            if(!gap[dep[u]])
            {
                for(int i = 1; i <= n; i ++ )
                    if(i != s && i != t && dep[i] > dep[u] && dep[i] < n + 1)
                        dep[i] = n + 1;
            }
            relabel(u);
            gap[dep[u]] ++;
            q.push(u);
            is_in[u] = true;
        }
    }
    return flow[t];
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

    cout << maxflow() << endl;
    
    return 0;
}
