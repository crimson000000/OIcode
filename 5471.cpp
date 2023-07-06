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
int n, m, W, H;
struct jump
{
    int w, x1, y1, x2, y2;
};
vector<jump> ci[N];

struct poi
{
    int x, y, id;
}q[N], city[N];

inline bool cmp1(poi a, poi b)
{
    return a.x < b.x;
}

inline bool cmp2(poi a, poi b)
{
    return a.y < b.y;
}

struct kdt
{
    int l, r;
    int minx, maxx;
    int miny, maxy;
    int dist;
    int cnt;
}t[N];
int rt;

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

inline void pushdown(int p)
{
    if(t[p].l && t[t[p].l].dist > t[p].dist)
    {
        t[t[p].l].dist = t[p].dist;
        pushdown(t[p].l);
    }
    if(t[p].r && t[t[p].r].dist > t[p].dist)
    {
        t[t[p].r].dist = t[p].dist;
        pushdown(t[p].r);
    }
}

template <class T>
inline T sq(T a)
{
    return a * a;
}

int mp[N];
inline int build(int l, int r, int op)
{
    if(l > r) return 0;
    if(l == r)
    {
        pushup(l);
        t[l].cnt = q[l].id;
        mp[q[l].id] = l;
        return l;
    }
    int mid = l + r >> 1;
    // double avx = 0, avy = 0, vax = 0, vay = 0;
    // for(int i = l; i <= r; i ++ )
    //     avx += q[i].x, avy += q[i].y;
    
    // avx /= (double)(r - l + 1);
    // avy /= (double)(r - l + 1);

    // for(int i = l; i <= r; i ++ )
    //     vax += sq(avx - q[i].x), vay += sq(avy - q[i].y);

    if(op)
    {
        nth_element(q + l, q + mid, q + r + 1, cmp1);
    }
    else 
    {
        nth_element(q + l, q + mid, q + r + 1, cmp2);
    }
    t[mid].l = build(l, mid - 1, op ^ 1);
    t[mid].r = build(mid + 1, r, op ^ 1);
    t[mid].cnt = q[mid].id;
    mp[q[mid].id] = mid;
    pushup(mid);
    return mid;
}

priority_queue<PII, vector<PII>, greater<PII>> heap;
bitset<N> st;
int dist[N];

inline void relax(int p, int xl, int yl, int xr, int yr, int d)
{
    if(!p) return;
    if(xl > t[p].maxx || xr < t[p].minx || yl > t[p].maxy || yr < t[p].miny) return;
    if(xl <= t[p].minx && xr >= t[p].maxx && yl <= t[p].miny && yr >= t[p].maxy)
    {
        if(dist[p + n] > d)
        {
            dist[p + n] = d;
            heap.push({d, p + n});
        }
        // cout << p + n << endl;
        return;
    }
    if(city[t[p].cnt].x >= xl && city[t[p].cnt].x <= xr &&
        city[t[p].cnt].y >= yl && city[t[p].cnt].y <= yr)
        if(dist[t[p].cnt] > d)
        {
            dist[t[p].cnt] = d;
            heap.push({d, t[p].cnt});
            // cout << t[p].cnt << endl;
        }
        
    relax(t[p].l, xl, yl, xr, yr, d);
    relax(t[p].r, xl, yl, xr, yr, d);
}

void dijkstra(int s)
{
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    heap.push({0, s});

    while(heap.size())
    {
        auto ttt = heap.top();
        heap.pop();

        int ver = ttt.second, distance = ttt.first;
        if(st[ver]) continue;
        st[ver] = true;

        // printf("%d can relax:\n", ver);

        if(ver > n)
        {
            int now = ver - n;
            if(dist[t[now].cnt] > distance)
            {
                dist[t[now].cnt] = distance;
                heap.push({distance, t[now].cnt}); 
                // cout << t[now].cnt << endl;
            }
            if(t[now].l && dist[t[now].l + n] > distance)
            {
                dist[t[now].l + n] = distance;
                heap.push({distance, t[now].l + n});
                // cout << t[now].l + n << endl;
            }
            if(t[now].r && dist[t[now].r + n] > distance)
            {
                dist[t[now].r + n] = distance;
                heap.push({distance, t[now].r + n});
                // cout << t[now].r + n << endl;
            }
        }
        else
        {
            for(auto l : ci[ver])
            {
                int x1 = l.x1, y1 = l.y1, x2 = l.x2, y2 = l.y2;
                int newdist = distance + l.w;
                // printf("%d %d %d %d\n", x1, y1, x2, y2);
                relax(rt, x1, y1, x2, y2, newdist);
            }
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), W = read(), H = read();
    
    for(int i = 1; i <= n; i ++ ) 
    {
        q[i].x = read(), q[i].y = read(), q[i].id = i;
        city[i] = q[i];
    }

    rt = build(1, n, 1);

    // for(int i = 1; i <= n; i ++ ) 
    // {
    //     printf("%d %d (%d, %d, %d)\n", i, t[i].cnt, q[i].x, q[i].y, q[i].id);
    // }

    // printf("%d %d %d %d\n", t[rt].minx, t[rt].miny, t[rt].maxx, t[rt].maxy);

    for(int i = 1; i <= m; i ++ )
    {
        int p = read(), t = read(), x1 = read(), x2 = read(), y1 = read(), y2 = read();
        ci[p].push_back({t, x1, y1, x2, y2});
    }

    // for(int i = 1; i <= n; i ++ )
    // {
    //     printf("%d: ", i);
    //     for(auto t : ci[i])
    //         printf("%d %d %d %d %d\n", t.x1, t.y1, t.x2, t.y2, t.w);
    // }

    dijkstra(1);

    for(int i = 2; i <= n; i ++ )
        printf("%d\n", dist[i]);

    return 0;
}