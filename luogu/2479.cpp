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

const int N = 2e5 + 10, INF = 0x3f3f3f3f;
const double alpha = 0.725;
struct poi
{
    ll x, y;
}q[N];

inline bool cmp1(poi a, poi b)
{
    return a.x < b.x;
}

inline bool cmp2(poi a, poi b)
{
    return a.y < b.y;
}

struct node
{
    int l, r;
    int minx, maxx;
    int miny, maxy;
    int siz, d;
}t[N];
int g[N], tt;
int n;

inline void pushup(int p)
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

template <class T>
inline T sq(T a)
{
    return a * a;
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
        avx += q[i].x, avy = q[i].y;
    
    avx /= (double)(r - l + 1);
    avy /= (double)(r - l + 1);

    for(int i = l; i <= r; i ++ )
        vax += sq(q[i].x - avx), vay += sq(q[i].y - avy);
    
    if(vax > vay)
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

inline ll dist(int a, int b)
{
    return abs(q[a].x - q[b].x) + abs(q[a].y - q[b].y);
}

inline ll dist(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

inline ll f1(int a, int b)
{
    ll res = 0;
    if(t[b].minx > q[a].x) res += abs(t[b].minx - q[a].x);
    if(t[b].maxx < q[a].x) res += abs(t[b].maxx - q[a].x);
    if(t[b].miny > q[a].y) res += abs(t[b].miny - q[a].y);
    if(t[b].maxy < q[a].y) res += abs(t[b].maxy - q[a].y);
    return res;
}

inline ll f2(int a, int b)
{
    ll res = 0;
    res = max(res, dist(q[a].x, q[a].y, t[b].maxx, t[b].maxy));
    res = max(res, dist(q[a].x, q[a].y, t[b].maxx, t[b].miny));
    res = max(res, dist(q[a].x, q[a].y, t[b].minx, t[b].maxy));
    res = max(res, dist(q[a].x, q[a].y, t[b].minx, t[b].miny));
    return res;
}

ll ansmin = INF, ansmax, ans;
void querymax(int l, int r, int x)
{
    if(l > r) return;
    int mid = l + r >> 1;
    if(x != mid) 
    {
        ansmin = min(ansmin, dist(x, mid));
        ansmax = max(ansmax, dist(x, mid));
    }
    if(l == r) return;
    ll distl = f2(x, t[mid].l), distr = f2(x, t[mid].r);
    if(distl >= ansmax && distr >= ansmax)
    {
        if(distl >= distr) 
        {
            querymax(l, mid - 1, x);
            if(distr >= ansmax) querymax(mid + 1, r, x);
        }
        else
        {
            querymax(mid + 1, r, x);
            if(distl >= ansmax) querymax(l, mid - 1, x);
        }
    }
    else
    {
        if(distl >= ansmax) querymax(l, mid - 1, x);
        if(distr >= ansmax) querymax(mid + 1, r, x);
    }
}

void querymin(int l, int r, int x)
{
    if(l > r) return;
    int mid = l + r >> 1;
    if(x != mid) 
    {
        ansmin = min(ansmin, dist(x, mid));
        ansmax = max(ansmax, dist(x, mid));
    }
    if(l == r) return;
    ll distl = f1(x, t[mid].l), distr = f1(x, t[mid].r);
    if(distl <= ansmin && distr <= ansmin)
    {
        if(distl < distr) 
        {
            querymin(l, mid - 1, x);
            if(distr <= ansmin) querymin(mid + 1, r, x);
        }
        else
        {
            querymin(mid + 1, r, x);
            if(distl <= ansmin) querymin(l, mid - 1, x);
        }
    }
    else
    {
        if(distl <= ansmin) querymin(l, mid - 1, x);
        if(distr <= ansmin) querymin(mid + 1, r, x);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) q[i].x = read(), q[i].y = read();

    build(1, n);
    ans = INF;
    for(int i = 1; i <= n; i ++ )
    {
        ansmin = INF, ansmax = 0;
        querymax(1, n, i), querymin(1, n, i);
        // cout << ansmax << ' ' << ansmin << endl;
        ans = min(ans, ansmax - ansmin);
    }

    cout << ans << endl;

    return 0;
}