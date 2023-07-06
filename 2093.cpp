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

const int N = 1e6 + 10;
struct kdt
{
    int l, r;
    int minx, maxx;
    int miny, maxy;
}t[N];
int rt;
int n, m;
struct Ans
{
    int id;
    ll dist;
    Ans(ll _d, int _id): id(_id), dist(_d) {}

    bool operator < (const Ans& a) const
    {
        if(dist != a.dist) return dist < a.dist;
        return id > a.id;
    }

    bool operator > (const Ans& a) const
    {
        if(dist != a.dist) return dist > a.dist;
        return id < a.id;
    }
};

priority_queue<Ans, vector<Ans>, greater<Ans>> heap;

struct poi
{
    int x, y, id;
}q[N];

inline bool cmp1(poi a, poi b)
{
    return a.x < b.x;
}

inline bool cmp2(poi a, poi b)
{
    return a.y < b.y;
}

inline void pushup(int p)
{
    t[p].minx = t[p].maxx = q[p].x;
    t[p].miny = t[p].maxy = q[p].y;
    if(t[p].l)
    {
        t[p].minx = min(t[p].minx, t[t[p].l].minx);
        t[p].maxx = max(t[p].maxx, t[t[p].l].maxx);
        t[p].miny = min(t[p].miny, t[t[p].l].miny);
        t[p].maxy = max(t[p].maxy, t[t[p].l].maxy);
    }
    if(t[p].r)
    {
        t[p].minx = min(t[p].minx, t[t[p].r].minx);
        t[p].maxx = max(t[p].maxx, t[t[p].r].maxx);
        t[p].miny = min(t[p].miny, t[t[p].r].miny);
        t[p].maxy = max(t[p].maxy, t[t[p].r].maxy);
    }
}

inline int build(int l, int r, int op)
{
    if(l > r) return 0;
    if(l == r)
    {
        pushup(l);
        return l;
    }
    int mid = l + r >> 1;
    if(op) nth_element(q + l, q + mid, q + r + 1, cmp1);
    else nth_element(q + l, q + mid, q + r + 1, cmp2);
    t[mid].l = build(l, mid - 1, op ^ 1);
    t[mid].r = build(mid + 1, r, op ^ 1);
    pushup(mid);
    return mid;
}

inline ll sq(ll a)
{
    return a * a;
}

inline ll dis(poi a, poi b)
{
    return sq(a.x - b.x) + sq(a.y - b.y);
}

inline ll f(int p, poi a)
{
    ll res = 0;
    res = max(res, dis(a, {t[p].minx, t[p].miny}));
    res = max(res, dis(a, {t[p].minx, t[p].maxy}));
    res = max(res, dis(a, {t[p].maxx, t[p].miny}));
    res = max(res, dis(a, {t[p].maxx, t[p].maxy}));
    return res;
}

inline void query(int p, poi a)
{
    if(!p) return;
    if(f(p, a) < heap.top().dist) return;
    ll dist = dis(q[p], a);
    if(Ans(dist, q[p].id) > heap.top()) 
    {
        heap.pop();
        heap.push(Ans(dist, q[p].id));
    }
    ll distl = f(t[p].l, a), distr = f(t[p].r, a);
    if(distl > distr)
    {
        if(Ans(distl, 0) > heap.top()) query(t[p].l, a);
        if(Ans(distr, 0) > heap.top()) query(t[p].r, a);
    }
    else 
    {
        if(Ans(distr, 0) > heap.top()) query(t[p].r, a);
        if(Ans(distl, 0) > heap.top()) query(t[p].l, a);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int x = read(), y = read();
        q[i] = {x, y, i};
    }

    rt = build(1, n, 0);

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int x = read(), y = read(), k = read();
        while(heap.size()) heap.pop();
        for(int i = 1; i <= k; i ++ ) heap.push(Ans(0, n + 1));
        query(rt, {x, y, 0});
        printf("%d\n", heap.top().id);
    }

    return 0;
}
