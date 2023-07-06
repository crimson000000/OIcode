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
struct node
{
    int l, r;
    double minx, maxx;
    double miny, maxy;
    int d;
}t[N];

struct point
{
    double x, y;
}q[N];
int n;

inline bool cmp1(point a, point b)
{
    return a.x < b.x;
}

inline bool cmp2(point a, point b)
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

int build(int l, int r)
{
    if(l > r) return 0;
    if(l == r)
    {
        pushup(l);
        return l;
    }
    int mid = l + r >> 1;
    double avx = 0, avy = 0, vax = 0, vay = 0;
    for(int i = l; i <= r; i ++ )
        avx += q[i].x, avy += q[i].y;
    
    avx /= (double)(r - l + 1);
    avy /= (double)(r - l + 1);

    for(int i = l; i <= r; i ++ )
        vax += (q[i].x - avx) * (q[i].x - avx), vay += (q[i].y - avy) * (q[i].y - avy);
    
    if(vax < vay)
    {
        t[mid].d = 1;
        nth_element(q + l, q + mid, q + r + 1, cmp1);
    }
    else
    {
        t[mid].d = 2;
        nth_element(q + l, q + mid, q + r + 1, cmp2);
    }
    t[mid].l = build(l, mid - 1);
    t[mid].r = build(mid + 1, r);
    pushup(mid);
    return mid;
}

inline double f(int a, int b)
{
    double ret = 0;
    if(t[b].minx > q[a].x) ret += (t[b].minx - q[a].x) * (t[b].minx - q[a].x);
    if(t[b].maxx < q[a].x) ret += (t[b].maxx - q[a].x) * (t[b].maxx - q[a].x);
    if(t[b].miny > q[a].y) ret += (t[b].miny - q[a].y) * (t[b].miny - q[a].y);
    if(t[b].maxy < q[a].y) ret += (t[b].maxy - q[a].y) * (t[b].maxy - q[a].y);
    return ret;
}

inline double dist(int a, int b)
{
    return (q[a].x - q[b].x) * (q[a].x - q[b].x) + (q[a].y - q[b].y) * (q[a].y - q[b].y);
}

double ans = 1e20;
void query(int l, int r, int x)
{
    if(l > r) return;
    int mid = l + r >> 1;
    if(mid != x) ans = min(ans, dist(x, mid));
    if(l == r) return;
    double distl = f(x, t[mid].l), distr = f(x, t[mid].r);
    if(distl < ans && distr < ans)
    {
        if(distl < distr)
        {
            query(l, mid - 1, x);
            if(distr < ans) query(mid + 1, r, x);
        }
        else
        {
            query(mid + 1, r, x);
            if(distl < ans) query(l, mid - 1, x);
        }
    }
    else
    {
        if(distl < ans) query(l, mid - 1, x);
        if(distr < ans) query(mid + 1, r, x);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        q[i].x = read(), q[i].y = read(); 
    }

    build(1, n);
    for(int i = 1; i <= n; i ++ ) query(1, n, i);
    printf("%.4lf\n", sqrt(ans));

    return 0;
}