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
struct point
{
    ll x, y;
}q[N];

inline bool cmp1(point a, point b)
{
    return a.x < b.x;
}

inline bool cmp2(point a, point b)
{
    return a.y < b.y;
}

struct kdt
{
    int l, r;
    ll minx, maxx;
    ll miny, maxy;
}t[N];
priority_queue<ll, vector<ll>, greater<ll>> heap;
int n, k;

inline void pushup(int p)
{
    t[p].maxx = t[p].minx = q[p].x;
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

template<class T>
inline T sq(T a)
{
    return a * a;
}

inline int build(int l, int r)
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
        vax += sq(avx - q[i].x), vay += sq(avy - q[i].y);
    
    if(vax < vay)
    {
        nth_element(q + l, q + mid, q + r + 1, cmp1);
    }
    else
    {
        nth_element(q + l, q + mid, q + r + 1, cmp2);
    }
    t[mid].l = build(l, mid - 1);
    t[mid].r = build(mid + 1, r);
    pushup(mid);
    return mid;
}

inline ll dist(int a, int b)
{
    return sq(q[a].x - q[b].x) + sq(q[a].y - q[b].y);
}

inline ll f(int a, int b)
{
    return max(sq(q[a].x - t[b].maxx), sq(q[a].x - t[b].minx)) + 
            max(sq(q[a].y - t[b].maxy), sq(q[a].y - t[b].miny));
}

void query(int l, int r, int x)
{
    if(l > r) return;
    int mid = l + r >> 1;
    ll now = dist(mid, x);
    if(now > heap.top()) heap.pop(), heap.push(now);
    ll distl = f(x, t[mid].l), distr = f(x, t[mid].r);
    if(distl > heap.top() && distr > heap.top())
    {
        if(distl > distr)
        {
            query(l, mid - 1, x);
            if(distr > heap.top()) query(mid + 1, r, x);
        }
        else
        {
            query(mid + 1, r, x);
            if(distl > heap.top()) query(l, mid - 1, x);
        }
    }
    else
    {
        if(distl > heap.top()) query(l, mid - 1, x);
        if(distr > heap.top()) query(mid + 1, r, x);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    k <<= 1;
    for(int i = 1; i <= k; i ++ ) heap.push(0);

    for(int i = 1; i <= n; i ++ ) q[i].x = read(), q[i].y = read();

    build(1, n);
    for(int i = 1; i <= n; i ++ ) query(1, n, i);

    cout << heap.top() << endl;

    return 0;
}