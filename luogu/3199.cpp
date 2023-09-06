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
        x = ((x << 3) + (x << 1) + ch - '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
int h[3010], e[N], ne[N], idx;
double w[N];
int st;
int n, m;

struct edge
{
    int a, b;
    double c;
}ed[N];

inline void add(int a, int b, double c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline bool bfs(int st)
{
    queue<int> q;
    while(q.size()) q.pop();
    bitset<3010> vis;
    vis.reset();
    q.push(st);
    vis[st] = true;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(!vis[v])
            {
                q.push(v);
                vis[v] = true;
            }
        }
    }
    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
            return false;
    return true;
}

int cnt[3010];
double dist[3010];
bitset<3010> vis;
queue<int> q;
inline bool spaf(double mid)
{
    memset(cnt, 0, sizeof cnt);
    vis.reset();
    for(int i = 1; i <= n; i ++ ) dist[i] = 1e20;
    while(q.size()) q.pop();
    q.push(st);
    dist[st] = 0;
    vis[st] = true;
    int count = 0;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > dist[u] + w[i] - mid)
            {
                dist[v] = dist[u] + w[i] - mid;
                cnt[v] = cnt[u] + 1;
                count ++;
                if(count > n * 6) return true;
                if(cnt[v] > n) return true;
                if(!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

inline bool check(double mid)
{
    return spaf(mid);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        double c;
        scanf("%lf", &c);
        ed[i] = {a, b, c};
        add(a, b, c);
    }

    for(int i = 1; i <= n; i ++ )
        if(bfs(i))
        {
            st = i;
            break;
        }

    double l = -1e7, r = 1e7;
    while(r - l > 1e-10)
    {
        double mid = (l + r) / 2;
        if(!check(mid)) l = mid;
        else r = mid;
    }

    printf("%.8lf\n", l);

    return 0;
}