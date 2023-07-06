#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;
#define int ll

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

const int N = 1e6 + 10;
struct query
{
    int x, y, op;
    bool operator < (const query& a) const
    {
        if(x != a.x) return x < a.x;
        return y < a.y;
    }
};
set<query> mp;

struct node
{
    int l, r;
    vector<query> q;
}t[N << 2];
int n, m;

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline void change(int p, int l, int r, query a)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].q.emplace_back(a);
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, a);
    if(r > mid) change(p << 1 | 1, l, r, a);
}

unordered_map<int, int> a1, a2;
int tot1, tot2;

int fa[N], siz[N], ycnt[N];
vector<pair<int, int&>> hfa, hsiz, hy;
ll nans;

inline int find(int x)
{
    while(x != fa[x]) x = fa[x];
    return x;
}

inline void merge(int x, int y)
{
    int fx = find(x), fy = find(y);
    if(fx == fy) return;
    if(siz[fx] > siz[fy]) swap(fx, fy);
    hfa.emplace_back(fa[fx], fa[fx]);
    hsiz.emplace_back(siz[fy], siz[fy]);
    hy.emplace_back(ycnt[fy], ycnt[fy]);

    nans -= ycnt[fx] * (siz[fx] - ycnt[fx]);
    nans -= ycnt[fy] * (siz[fy] - ycnt[fy]);

    fa[fx] = fy;
    siz[fy] += siz[fx];
    ycnt[fy] += ycnt[fx];

    nans += ycnt[fy] * (siz[fy] - ycnt[fy]);
}

inline int history()
{
    return hfa.size();
}

inline void roll(int h)
{
    while(history() > h)
    {
        hfa.back().second = hfa.back().first;
        hsiz.back().second = hsiz.back().first;
        hy.back().second = hy.back().first;
        hfa.pop_back();
        hsiz.pop_back();
        hy.pop_back();
    }
}

inline int id(int a, int x_or_y)
{
    return a + n * x_or_y;
}

ll ans[N];
void dfs(int p)
{
    if(t[p].l == t[p].r)
    {
        int h = history();
        int tmp = nans;
        for(auto u : t[p].q) merge(id(u.x, 0), id(u.y, 1));
        ans[t[p].l] = nans;
        roll(h);
        nans = tmp;
        return;
    }

    int h = history();
    int tmp = nans;
    for(auto u : t[p].q) merge(id(u.x, 0), id(u.y, 1));
    dfs(p << 1);
    dfs(p << 1 | 1);
    roll(h);
    nans = tmp;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\noip\\in.in", "r", stdin);
        freopen("D:\\noip\\out.out", "w", stdout);
    #endif

    n = read();

    build(1, 1, n);

    for(int i = 1; i <= n; i ++ ) fa[i] = i, siz[i] = 1;
    for(int i = n + 1; i <= 2 * n; i ++ ) fa[i] = i, siz[i] = 1, ycnt[i] = 1;
    
    for(int i = 1; i <= n; i ++ )
    {
        int x = read(), y = read();
        if(!a1[x]) a1[x] = ++ tot1;
        x = a1[x];

        if(!a2[y]) a2[y] = ++ tot2;
        y = a2[y];

        if(mp.count({x, y, i})) 
        {
            auto it = mp.lower_bound({x, y, i});
            change(1, it -> op, i - 1, {x, y, i});
            mp.erase(it);
        }
        else mp.insert({x, y, i});
    }

    for(auto it = mp.begin(); it != mp.end(); it ++ )
        change(1, it -> op, n, {it -> x, it -> y, it -> op});
    
    dfs(1);

    for(int i = 1; i <= n; i ++ ) printf("%lld ", ans[i]);

    return 0;
}
