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

const int N = 2e6 + 10;
int h[N], e[N], ne[N], w[N], idx;
struct edge
{
    int a, b, w, h;
    bool operator < (const edge& ed) const
    {
        return h > ed.h;
    }
}ed[N];
int n, m;
int Q, K, S;
ll lastans;

inline void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

namespace spaf
{
    ll dist[N];
    bitset<N> st;
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    inline void SPAF(int s)
    {
        memset(dist, 0x3f, sizeof dist);
        st.reset();
        heap.push({0, s});
        dist[s] = 0;

        while(heap.size())
        {
            auto t = heap.top();
            heap.pop();
            
            int ver = t.second;
            if(st[ver]) continue;
            st[ver] = true;

            for(int i = h[ver]; i != -1; i = ne[i])
            {
                int v = e[i];
                if(dist[v] > dist[ver] + w[i])
                {
                    dist[v] = dist[ver] + w[i];
                    heap.push({dist[v], v});
                }
            }
        }
    }
}

struct node
{
    int l, r;
    ll val;
}t[N * 30];
int rootfa[N], rootdep[N], rootmin[N], cnt;
int fa_idx;

inline int buildfa(int l, int r)
{
    int p = ++ cnt;
    if(l == r)
    {
        t[p].val = ++ fa_idx;
        return p;
    }
    int mid = l + r >> 1;
    t[p].l = buildfa(l, mid);
    t[p].r = buildfa(mid + 1, r);
    return p;
}

int dist_idx;
inline int builddist(int l, int r)
{
    int p = ++ cnt;
    if(l == r)
    {
        ++ dist_idx;
        t[p].val = spaf::dist[dist_idx];
        return p;
    }
    int mid = l + r >> 1;
    t[p].l = builddist(l, mid);
    t[p].r = builddist(mid + 1, r);
    return p;
}

inline void change(int &p, int q, int l, int r, int pos, ll val)
{
    p = ++ cnt;
    t[p] = t[q];
    if(l == r)
    {
        t[p].val = val;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) change(t[p].l, t[q].l, l, mid, pos, val);
    else change(t[p].r, t[q].r, mid + 1, r, pos, val);
}

inline ll query(int p, int l, int r, int pos)
{
    if(!p) return 0;
    if(l == r) return t[p].val;
    int mid = l + r >> 1;
    if(pos <= mid) return query(t[p].l, l, mid, pos);
    else return query(t[p].r, mid + 1, r, pos);
}

inline int find(int ver, int x)
{
    int fa = query(rootfa[ver], 1, n, x);
    return fa == x ? x : find(ver, fa);
}

inline void merge(int ver, int x, int y)
{
    int fx = find(ver - 1, x), fy = find(ver - 1, y);
    if(fx == fy)
    {
        rootfa[ver] = rootfa[ver - 1];
        rootdep[ver] = rootdep[ver - 1];
        rootmin[ver] = rootmin[ver - 1];
        return;
    }
    int dx = query(rootdep[ver - 1], 1, n, fx);
    int dy = query(rootdep[ver - 1], 1, n, fy);
    if(dx < dy)
    {
        change(rootfa[ver], rootfa[ver - 1], 1, n, fx, fy);
        rootdep[ver] = rootdep[ver - 1];
        ll mdis = min(query(rootmin[ver - 1], 1, n, fx), query(rootmin[ver - 1], 1, n, fy));
        change(rootmin[ver], rootmin[ver - 1], 1, n, fy, mdis);
    }
    else if(dy < dx)
    {
        change(rootfa[ver], rootfa[ver - 1], 1, n, fy, fx);
        rootdep[ver] = rootdep[ver - 1];
        ll mdis = min(query(rootmin[ver - 1], 1, n, fx), query(rootmin[ver - 1], 1, n, fy));
        change(rootmin[ver], rootmin[ver - 1], 1, n, fx, mdis);
    }
    else
    {
        change(rootfa[ver], rootfa[ver - 1], 1, n, fy, fx);
        change(rootdep[ver], rootdep[ver - 1], 1, n, fx, dx + 1);
        ll mdis = min(query(rootmin[ver - 1], 1, n, fx), query(rootmin[ver - 1], 1, n, fy));
        change(rootmin[ver], rootmin[ver - 1], 1, n, fx, mdis);
    }
}

namespace uni
{
    int p[N], siz[N];
    inline int find(int x)
    {
        if(p[x] != x) p[x] = find(p[x]);
        return p[x];
    }

    inline void merge(int x, int y)
    {
        x = find(x), y = find(y);
        if(x == y) return;
        if(siz[x] < siz[y])
        {
            p[x] = y;
            siz[y] += siz[x];
        }
        else 
        {
            p[y] = x;
            siz[x] += siz[y];
        }
    }
}

inline void kruskal()
{
    rootfa[0] = buildfa(1, n);
    rootmin[0] = builddist(1, n);
    for(int i = 1; i <= n; i ++ ) uni::p[i] = i, uni::siz[i] = 1;
    int cnt = n;
    bool flag = false;
    for(int i = 1; i <= m; i ++ )
    {
        if(flag)
        {
            rootdep[i] = rootdep[i - 1];
            rootfa[i] = rootfa[i - 1];
            rootmin[i] = rootmin[i - 1];
            continue;
        }
        int x = ed[i].a, y = ed[i].b;
        if(uni::find(x) == uni::find(y)) 
        {
            rootdep[i] = rootdep[i - 1];
            rootfa[i] = rootfa[i - 1];
            rootmin[i] = rootmin[i - 1];
            continue;
        }
        merge(i, x, y);
        if(uni::find(x) != uni::find(y))
        {
            uni::merge(x, y);
            cnt --;
        }
        if(cnt == 1) flag = true;
    }
}

inline void init()
{
    idx = 0;
    fa_idx = 0;
    dist_idx = 0;
    cnt = 0;
    lastans = 0;
    memset(rootfa, 0, sizeof rootfa);
    memset(rootdep, 0, sizeof rootdep);
    memset(rootmin, 0, sizeof rootmin);
    memset(h, -1, sizeof h);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();

    while(T -- )
    {
        init();

        n = read(), m = read();
        for(int i = 1; i <= m; i ++ )
        {
            int a = read(), b = read(), l = read(), he = read();
            add(a, b, l), add(b, a, l);
            ed[i] = {a, b, l, he};
        }

        spaf::SPAF(1);
        
        sort(ed + 1, ed + m + 1);

        // for(int i = 1; i <= m; i ++ ) printf("%d ", ed[i].h);
        // puts("");

        kruskal();

        // for(int i = 1; i <= n; i ++ ) printf("%d: %d\n", i, query(rootfa[2], 1, n, i));
        // double st = clock();
        Q = read(), K = read(), S = read();
        while(Q -- )
        {
            int v = read(), p = read();
            v = (v + K * lastans - 1) % n + 1;
            p = (p + K * lastans) % (S + 1);

            int l = 0, r = m;
            while(l < r)
            {
                int mid = l + r + 1 >> 1;
                if(p < ed[mid].h) l = mid;
                else r = mid - 1;
            }

            // cout << l << endl;

            int ver = l;
            int fa = find(ver, v);
            printf("%lld\n", lastans = query(rootmin[ver], 1, n, fa));
        }
        // printf("%.3lf\n", (clock() - st) / CLOCKS_PER_SEC);
    }
    return 0;
}