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
int h[N], e[N], ne[N], w[N], idx;
bitset<N> st;
queue<int> q;
int dist[N];

struct E
{
    int u, v, a, b;
    bool operator < (const E &e) const
    {
        return a < e.a;
    }
}ed[N];
int n, m;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void spfa()
{
    while(q.size())
    {
        int u = q.front();
        st[u] = false;
        q.pop();

        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            if(dist[v] > max(dist[u], w[i]))
            {
                dist[v] = max(dist[u], w[i]);
                if(!st[v])
                {
                    q.push(v);
                    st[v] = true;
                }
            }
        }
    }
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
        int u = read(), v = read(), a = read(), b = read();
        ed[i] = {u, v, a, b};
    }

    sort(ed + 1, ed + m + 1);

    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;

    int ans = INF;

    for(int i = 1; i <= m; i ++ )
    {
        add(ed[i].u, ed[i].v, ed[i].b);
        add(ed[i].v, ed[i].u, ed[i].b);

        q.push(ed[i].u), q.push(ed[i].v);
        st[ed[i].u] = st[ed[i].v] = true;

        spfa();

        if(dist[n] != n)
            ans = min(ans, ed[i].a + dist[n]);
    }

    if(ans != INF) cout << ans << endl;
    else puts("-1");

    return 0;
}