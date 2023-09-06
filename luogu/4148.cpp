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

const int N = 2e5 + 10;
const double alpha = 0.725;
struct poi
{
    int x, y, val;
}q[N];

inline bool cmp1(int a, int b)
{
    return q[a].x < q[b].x;
}

inline bool cmp2(int a, int b)
{
    return q[a].y < q[b].y;
}

struct node
{
    int l, r;
    int sum, siz;
    int minx, maxx;
    int miny, maxy;
    int d;
}t[N];
int g[N], tt;
int rt;
int n, cur;
int lastans;

inline void pushup(int p)
{
    t[p].minx = t[p].maxx = q[p].x;
    t[p].miny = t[p].maxy = q[p].y;
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
    t[p].sum = t[t[p].l].sum + t[t[p].r].sum + q[p].val;
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

template <class T>
inline T sq(T a)
{
    return a * a;
}

inline int build(int l, int r)
{
    if(l > r) return 0;
    int mid = l + r >> 1;
    double avx = 0, avy = 0, vax = 0, vay = 0;
    for(int i = l; i <= r; i ++ )
        avx += q[g[i]].x, avy += q[g[i]].y;
    
    avx /= (double)(r - l + 1);
    avy /= (double)(r - l + 1);

    for(int i = l; i <= r; i ++ )
        vax += sq(q[g[i]].x - avx), vay += sq(q[g[i]].y - avy);

    if(vax > vay)
    {
        t[g[mid]].d = 1;
        nth_element(g + l, g + mid, g + r + 1, cmp1);
    }
    else
    {
        t[g[mid]].d = 2;
        nth_element(g + l, g + mid, g + r + 1, cmp2);
    }

    t[g[mid]].l = build(l, mid - 1);
    t[g[mid]].r = build(mid + 1, r);
    pushup(g[mid]);
    return g[mid];
}

void pia(int x)
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
    x = build(1, tt);
}

inline bool fuck(int x)
{
    return alpha * t[x].siz <= (double)max(t[t[x].l].siz, t[t[x].r].siz);
}

void insert(int &x, int v)
{
    if(!x) 
    {
        x = v;
        pushup(x);
        return;
    }
    if(t[x].d == 1)
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
    pushup(x);
    if(fuck(x)) rebuild(x);
}

int query(int x, int xl, int yl, int xr, int yr)
{
    if(!x || xr < t[x].minx || xl > t[x].maxx || yr < t[x].miny || yl > t[x].maxy) return 0;
    if(xl <= t[x].minx && xr >= t[x].maxx && yl <= t[x].miny && yr >= t[x].maxy) return t[x].sum;
    int res = 0;
    if(q[x].x >= xl && q[x].x <= xr && q[x].y >= yl && q[x].y <= yr) 
        res += q[x].val;
    return query(t[x].l, xl, yl, xr, yr) + query(t[x].r, xl, yl, xr, yr) + res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    int op;
    while(~scanf("%d", &op))
    {
        if(op == 1)
        {
            int x = read(), y = read(), val = read();
            
            x ^= lastans;
            y ^= lastans;
            val ^= lastans;

            cur ++;
            q[cur].x = x, q[cur].y = y, q[cur].val = val;
            insert(rt, cur);
        }
        else if(op == 2)
        {
            int x1 = read(), y1 = read(), x2 = read(), y2 = read();
            x1 ^= lastans;
            y1 ^= lastans;
            x2 ^= lastans;
            y2 ^= lastans;
            lastans = query(rt, x1, y1, x2, y2);
            printf("%d\n", lastans);
        }
        else return 0;
    }

    return 0;
}