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
const double alpha = 0.725;
struct poi
{
    int x, y, val;
}q[N];

inline bool cmp1(int a, int b) {return q[a].x < q[b].x;}
inline bool cmp2(int a, int b) {return q[a].y < q[b].y;}

struct kdt
{
    int l, r;
    int minx, maxx;
    int miny, maxy;
    int val, sum, siz;
    int d;
}t[N];
int g[N], tt, cur;
int rt;

inline void maintain(int p)
{
    t[p].minx = t[p].maxx = q[p].x;
    t[p].miny = t[p].maxy = q[p].y;
    t[p].val = q[p].val;
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum + t[p].val;
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

inline int build(int l, int r, int op)
{
    if(l > r) return 0;
    int mid = l + r >> 1;
    if(!op) nth_element(g + l, g + mid, g + r + 1, cmp1);
    else nth_element(g + l, g + mid, g + r + 1, cmp2);
    t[g[mid]].l = build(l, mid - 1, op ^ 1);
    t[g[mid]].r = build(mid + 1, r, op ^ 1);
    t[g[mid]].d = op;
    maintain(g[mid]);
    return g[mid];
}

inline bool fuck(int x)
{
    return t[x].siz * alpha <= (double)max(t[t[x].l].siz, t[t[x].r].siz);
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
    x = build(1, tt, 0);
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

inline int query(int p, int xl, int yl, int xr, int yr)
{
    if(!p) return 0;
    if(xl > t[p].maxx || xr < t[p].minx || yl > t[p].maxy || yr < t[p].miny) return 0;
    if(xl <= t[p].minx && xr >= t[p].maxx && yl <= t[p].miny && yr >= t[p].maxy) 
        return t[p].sum;
    int res = 0;
    if(q[p].x >= xl && q[p].x <= xr && q[p].y >= yl && q[p].y <= yr)
        res += q[p].val;
    return res + query(t[p].l, xl, yl, xr, yr) + query(t[p].r, xl, yl, xr, yr);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int op;
    while(1)
    {
        op = read();
        if(op == 0)
        {
            int w = read();
        }
        else if(op == 1)
        {
            int x = read(), y = read(), val = read();
            cur ++;
            q[cur].x = x, q[cur].y = y, q[cur].val = val;
            insert(rt, cur);
        }
        else if(op == 2)
        {
            int x1 = read(), y1 = read(), x2 = read(), y2 = read();
            printf("%d\n", query(rt, x1, y1, x2, y2));
        }
        else return 0;
        // printf("%d %d %d %d %d\n", t[rt].minx, t[rt].miny, t[rt].maxx, t[rt].maxy, t[rt].sum);
    }

    return 0;
}