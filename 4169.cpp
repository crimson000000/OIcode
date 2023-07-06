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
const double alpha = 0.725;
struct poi
{
    int x, y;
}q[N];
int n, m;

inline bool cmp1(int a, int b) {return q[a].x < q[b].x;}
inline bool cmp2(int a, int b) {return q[a].y < q[b].y;}

struct kdt
{
    int l, r;
    int minx, maxx;
    int miny, maxy;
    int d, siz;
}t[N];
int g[N], rt, tt, cur;

inline void maintain(int p)
{
    t[p].minx = t[p].maxx = q[p].x;
    t[p].miny = t[p].maxy = q[p].y;
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    if(t[p].l)
    {
        t[p].minx = min(t[p].minx, t[t[p].l].minx);
        t[p].miny = min(t[p].miny, t[t[p].l].miny);
        t[p].maxx = max(t[p].maxx, t[t[p].l].maxx);
        t[p].maxy = max(t[p].maxy, t[t[p].l].maxy);
    }
    if(t[p].r)
    {
        t[p].minx = min(t[p].minx, t[t[p].r].minx);
        t[p].miny = min(t[p].miny, t[t[p].r].miny);
        t[p].maxx = max(t[p].maxx, t[t[p].r].maxx);
        t[p].maxy = max(t[p].maxy, t[t[p].r].maxy);
    }
}

inline int build(int l, int r, bool op)
{
    if(l > r) return 0;
    int mid = l + r >> 1;
    if(!op) nth_element(g + l, g + mid, g + r + 1, cmp1);
    else nth_element(g + l, g + mid, g + r + 1, cmp2);
    t[g[mid]].l = build(l, mid - 1, op ^ 1);
    t[g[mid]].r = build(mid + 1, r, op ^ 1);
    maintain(g[mid]);
    t[g[mid]].d = op;
    return g[mid];
}

inline bool fuck(int x)
{
    return t[x].siz * alpha <= max(t[t[x].l].siz, t[t[x].r].siz);
}

inline void pia(int x)
{
    if(!x) return;
    pia(t[x].l);
    g[++ tt] = x;
    pia(t[x].r);
}

inline void rebuild(int &x)
{
    tt = 0;
    pia(x);
    x = build(1, tt, 1);
}

inline void insert(int &x, int v)
{
    if(!x)
    {
        x = v;
        maintain(x);
        return;
    }
    if(t[x].d == 0)
    {
        if(q[v].x <= q[x].x)
            insert(t[x].l, v);
        else insert(t[x].r, v);
    }
    else
    {
        if(q[v].y <= q[x].y)
            insert(t[x].l, v);
        else insert(t[x].r, v);
    }
    maintain(x);
    if(fuck(x)) rebuild(x);
}

inline int f(int p, poi a)
{
    int res = 0;
    if(t[p].minx > a.x) res += abs(t[p].minx - a.x);
    if(t[p].maxx < a.x) res += abs(t[p].maxx - a.x);
    if(t[p].miny > a.y) res += abs(t[p].miny - a.y);
    if(t[p].maxy < a.y) res += abs(t[p].maxy - a.y);
    return res;
}

inline int dist(poi a, poi b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}

int ans = INF;
inline void query(int p, poi a)
{
    if(!p) return;
    ans = min(ans, dist(q[p], a));
    int distl = f(t[p].l, a), distr = f(t[p].r, a);
    if(distl <= ans && distr <= ans)
    {
        if(distl < distr)
        {
            query(t[p].l, a);
            if(distr <= ans) query(t[p].r, a);
        }
        else
        {
            query(t[p].r, a);
            if(distl <= ans) query(t[p].l, a);
        }
    }
    else
    {
        if(distl <= ans) query(t[p].l, a);
        if(distr <= ans) query(t[p].r, a);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        q[i].x = read(), q[i].y = read();
        g[i] = ++ cur;
    }

    rt = build(1, n, 0);

    while(m -- )
    {
        int op = read(), x = read(), y = read();
        if(op == 1)
        {
            cur ++;
            q[cur].x = x, q[cur].y = y;
            insert(rt, cur);
        }
        else
        {
            poi a;
            a.x = x, a.y = y;
            ans = INF;
            query(rt, a);
            printf("%d\n", ans);
        }
    }

    return 0;
}