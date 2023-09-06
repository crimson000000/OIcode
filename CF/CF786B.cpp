#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> PII;

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

const int N = 1e6 + 10, M = 5e6 + 10;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int h[N], e[M], ne[M], w[M], idx;
ll dist[N];
int cnt;
int n, m, s;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

struct segment
{
    struct seg
    {
        int l, r;
        int id;
    }t[N << 2];

    inline void build(int p, int l, int r, int op)
    {
        t[p].id = ++ cnt;
        t[p].l = l, t[p].r = r;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid, op);
        build(p << 1 | 1, mid + 1, r, op);
        // add(t[p << 1].id, t[p].id, 0);
        // add(t[p << 1 | 1].id, t[p].id, 0);
        if(!op) 
        {
            add(t[p].id, t[p << 1].id, 0);
            add(t[p].id, t[p << 1 | 1].id, 0);
        }
        else
        {
            add(t[p << 1].id, t[p].id, 0);
            add(t[p << 1 | 1].id, t[p].id, 0);
        }
    }

    // op == 0: x -> [l, r]; else [l, r] -> x
    inline void exadd(int p, int l, int r, int x, int v, bool op)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            // cout << t[p].id << endl;
            if(!op) add(x, t[p].id, v);
            else add(t[p].id, x, v);
            return;
        }
        int mid = t[p].l + t[p].r >> 1;
        if(l <= mid) exadd(p << 1, l, r, x, v, op);
        if(r > mid) exadd(p << 1 | 1, l, r, x, v, op);
    }

    inline int query(int p, int pos)
    {
        if(t[p].l == t[p].r) return t[p].id;
        int mid = t[p].l + t[p].r >> 1;
        if(pos <= mid) return query(p << 1, pos);
        else return query(p << 1 | 1, pos);
    }
}t1, t2;

bitset<N> st;
priority_queue<PII, vector<PII>, greater<PII>> heap;
inline void dijkstra(int s)
{
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    heap.push({0, s});

    while(heap.size())
    {
        int u = heap.top().second;
        heap.pop();

        if(st[u]) continue;
        st[u] = true;
        
        for(int i = h[u]; i != -1; i = ne[i])
        {
            int v = e[i];
            // cout << u << ' ' << v << endl;
            if(dist[v] > dist[u] + w[i])
            {
                dist[v] = dist[u] + w[i];
                heap.push({dist[v], v});
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

    n = read(), m = read(), s = read();

    t1.build(1, 1, n, 0);
    t2.build(1, 1, n, 1);

    for(int i = 1; i <= n; i ++ )
    {
        add(t1.query(1, i), t2.query(1, i), 0);
        add(t2.query(1, i), t1.query(1, i), 0);
    }

    while(m -- )
    {
        int op = read();
        if(op == 1)
        {
            int a = read(), b = read(), c = read();
            add(t1.query(1, a), t1.query(1, b), c);
            add(t2.query(1, a), t2.query(1, b), c);
        }
        else if(op == 2)
        {
            int a = read(), l = read(), r = read(), v = read();
            t1.exadd(1, l, r, t2.query(1, a), v, 0);
        }
        else
        {
            int a = read(), l = read(), r = read(), v = read();
            t2.exadd(1, l, r, t1.query(1, a), v, 1);
        }
    }

    dijkstra(t1.query(1, s));

    for(int i = 1; i <= n; i ++ )
        printf("%lld ", dist[t1.query(1, i)] == INF ? -1 : dist[t1.query(1, i)]);

    return 0;
}