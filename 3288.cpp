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
int h[N], e[N], ne[N], idx;
double cost[N];
int n, m;

struct edge
{
    int u, v, a, b, c, d;
}ed[N];

inline void add(int a, int b, double c)
{
    e[idx] = b, cost[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

queue<int> q;
bitset<N> st;
int cnt[N];
double dist[N];
inline bool spaf()
{
    for(int i = 1; i <= n + 2; i ++ ) cnt[i] = 0, dist[i] = 1e20;
    while(q.size()) q.pop();
    st.reset();
    q.push(n + 1);
    dist[n + 1] = 0;
    st[n + 1] = true;
    while(q.size())
    {
        int u = q.front();
        q.pop();
        st[u] = false;
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > dist[u] + cost[i])
            {
                dist[v] = dist[u] + cost[i];
                cnt[v] = cnt[u] + 1;
                if(cnt[v] > n) return true;
                if(!st[v])
                {
                    st[v] = true;
                    q.push(v);
                }
            }
        }
    }
    return false;
}

inline bool check(double mid)
{
    idx = 0;
    memset(h, -1, sizeof h);
    for(int i = 1; i <= m; i ++ )
    {
        int a = ed[i].a, b = ed[i].b, c = ed[i].c, d = ed[i].d;
        int u = ed[i].u, v = ed[i].v;
        add(u, v, mid + (b + d));
        if(c > 0) add(v, u, mid + (a - d));
    }
    return spaf();
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
        int u = read(), v = read(), a = read(), b = read(), c = read(), d = read();
        ed[i] = {u, v, a, b, c, d};
    }

    double l = 0, r = 10000;
    while(r - l > 1e-5)
    {
        double mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }

    printf("%.2lf\n", l);

    return 0;
}