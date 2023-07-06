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
    int maxx, minx;
    int maxy, miny;
    ll val, sum;
}t[N];
int n, rt, m;

struct poi
{
    int x, y, val;
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
    t[p].maxx = t[p].minx = q[p].x;
    t[p].maxy = t[p].miny = q[p].y;
    t[p].val = t[p].sum = q[p].val;
    if(t[p].l)
    {
        t[p].sum += t[t[p].l].sum;
        t[p].maxx = max(t[p].maxx, t[t[p].l].maxx);
        t[p].minx = min(t[p].minx, t[t[p].l].minx);
        t[p].maxy = max(t[p].maxy, t[t[p].l].maxy);
        t[p].miny = min(t[p].miny, t[t[p].l].miny);
    }
    if(t[p].r)
    {
        t[p].sum += t[t[p].r].sum;
        t[p].maxx = max(t[p].maxx, t[t[p].r].maxx);
        t[p].minx = min(t[p].minx, t[t[p].r].minx);
        t[p].maxy = max(t[p].maxy, t[t[p].r].maxy);
        t[p].miny = min(t[p].miny, t[t[p].r].miny);
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
    if(!op)
    {
        nth_element(q + l, q + mid, q + r + 1, cmp1);
    }
    else nth_element(q + l, q + mid, q + r + 1, cmp2);
    t[mid].l = build(l, mid - 1, op ^ 1);
    t[mid].r = build(mid + 1, r, op ^ 1);
    pushup(mid);
    return mid;
}

struct line
{
    int a, b, c;
}li[N];

inline bool in(poi x, line a)
{
    return (ll)x.x * a.a + x.y * a.b < (ll)a.c;
}

inline ll query(int p, line a)
{
    if(!in({t[p].maxx, t[p].maxy}, a) && !in({t[p].minx, t[p].miny}, a) && 
        !in({t[p].maxx, t[p].miny}, a) && !in({t[p].minx, t[p].maxy}, a)) return 0;
    if(in({t[p].maxx, t[p].maxy}, a) && in({t[p].minx, t[p].miny}, a) && 
        in({t[p].maxx, t[p].miny}, a) && in({t[p].minx, t[p].maxy}, a)) return t[p].sum;
    ll res = 0;
    if(in(q[p], a)) res += q[p].val;
    return res + query(t[p].l, a) + query(t[p].r, a);
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read(), m = read();
    
    for(int i = 1; i <= n; i ++ )
    {
        int x = read(), y = read(), w = read();
        q[i] = {x, y, w};
    }

    rt = build(1, n, 0);

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read(), c = read();
        printf("%lld\n", query(rt, {a, b, c}));
    }

    return 0;
}
