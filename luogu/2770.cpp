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

const int N = 1000 + 10, M = 1e6 + 10, INF = 0x3f3f3f3f;
int h[N], e[M], ne[M], w[M], cost[M], idx;
int dist[N], now[N];
int n, m, s, t;
int maxflow, flow, fee;
bool flag;

unordered_map<string, int> mp;
string city[N];
int in[N], out[N], cnt;

inline void add(int a, int b, int c, int d)
{
    e[idx] = b, w[idx] = c, cost[idx] = d, ne[idx] = h[a], h[a] = idx ++;
    e[idx] = a, w[idx] = 0, cost[idx] = -d, ne[idx] = h[b], h[b] = idx ++;
}

queue<int> q;
bitset<N> st;
bool spfa()
{
    memset(dist, -0x3f, sizeof dist);
    q.push(s);
    dist[s] = 0;
    st[s] = true;
    now[s] = h[s];

    while(q.size())
    {
        int u = q.front();
        q.pop();
        st[u] = false;

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(w[i] && dist[v] < dist[u] + cost[i])
            {
                dist[v] = dist[u] + cost[i];
                now[v] = h[v];
                if(!st[v])
                {
                    q.push(v);
                    st[v] = true;
                }
            }
        }
    }
    return dist[t] > -INF / 2;
}

bitset<N> vis;
inline int dinic(int u, int flow)
{
    if(u == t) return flow;
    vis[u] = true;
    int rest = flow, k;
    for(int i = now[u]; i != -1 && rest; i = ne[i])
    {
        now[u] = i;
        int v = e[i];
        if(w[i] && !vis[v] && dist[v] == dist[u] + cost[i])
        {
            k = dinic(v, min(w[i], rest));
            if(!k) dist[v] = -INF;
            w[i] -= k;
            w[i ^ 1] += k;
            rest -= k;
            fee += cost[i] * k;
        } 
    }
    vis[u] = false;
    return flow - rest;
}

bool vs[N];
void dfs1(int u)
{
    cout << city[u] << endl;
    vs[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v > n && v <= n * 2 && !w[i])
        {
            dfs1(v - n);
            break;
        }
    }
}

void dfs2(int u)
{
    vs[u] = true;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v > n && v <= n * 2 && !w[i] && !vs[v - n])
        {
            dfs2(v - n);
            break;
        }
    }
    cout << city[u] << endl;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n; i ++ )
    {
        cin >> city[i];
        mp[city[i]] = i;
        in[i] = i + n;
        out[i] = i;
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(i != 1 && i != n) add(in[i], out[i], 1, 1);
        else add(in[i], out[i], 2, 1);
    }

    while(m -- )
    {
        string s1, s2;
        cin >> s1 >> s2;
        int a = mp[s1], b = mp[s2];
        if(a > b) swap(a, b);
        if(a == 1 && b == n) flag = true;
        add(out[a], in[b], 1, 0);
    }

    s = N - 5 - n, t = N - 4 - n;
    add(s, in[1], INF, 0);
    add(out[n], t, INF, 0);

    while(spfa())
        while(flow = dinic(s, INF))
            maxflow += flow;
    
    if(maxflow == 2) cout << fee - 2 << endl;
    else if(maxflow == 1 && flag)
    {
        cout << 2 << endl;
        cout << city[1] << endl << city[n] << endl << city[1] << endl;
        return 0;
    }
    else
    {
        cout << "No Solution!" << endl;
        return 0;
    }

    dfs1(out[1]);
    dfs2(out[1]);

    return 0;
}