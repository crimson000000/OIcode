#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef pair<double, int> PDI;

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

const int N = 1e6 + 10, mod = 39989, mod2 = 1e9;
const int INF = 2e9;
const double eps = 1e-8;

struct seg
{
    double k, b;
    int l, r;
    seg() {k = b = 0;}
    seg(int x0, int y0, int x1, int y1)
    {
        if(x0 == x1)
        {
            k = 0;
            b = max(y0, y1);
            l = r = x0;
        }
        else
        {
            k = (double)(y1 - y0) / (x1 - x0);
            b = y0 - k * x0;
            l = min(x0, x1), r = max(x0, x1);
        }
    }
}a[N];

inline double f(int id, int x)
{
    if(x < a[id].l || x > a[id].r) return -INF;
    return a[id].k * x + a[id].b;
}

struct node
{
    int l, r;
    int maxn;
}t[N];
int root, cnt;

int n;
int lastans, sid;

inline void insert(int &p, int l, int r, int L, int R, int id)
{
    if(l > R || r < L) return;
    if(!p) p = ++ cnt;
    if(L <= l && r <= R)
    {
        if(t[p].maxn == 0) 
        {
            t[p].maxn = id;
            return;
        }
        int mid = l + r >> 1;
        if(f(id, mid) - f(t[p].maxn, mid) > eps) swap(id, t[p].maxn);
        if(f(id, l) - f(t[p].maxn, l) > eps || ((f(id, l) == f(t[p].maxn, l)) && id < t[p].maxn))
            insert(t[p].l, l, mid, L, R, id);
        if(f(id, r) - f(t[p].maxn, r) > eps || ((f(id, r) == f(t[p].maxn, r)) && id < t[p].maxn))
            insert(t[p].r, mid + 1, r, L, R, id);
        return;
    }
    int mid = l + r >> 1;
    if(L <= mid) insert(t[p].l, l, mid, L, R, id);
    if(R > mid) insert(t[p].r, mid + 1, r, L, R, id);
    return;
}

inline PDI max(PDI a, PDI b)
{
    if(a.first - b.first > eps) return a;
    else if(b.first - a.first > eps) return b;
    else if(a.second < b.second) return a;
    return b;
}

inline PDI query(int p, int l, int r, int pos)
{
    PDI ans = {-INF, 0};
    if(!p) return ans;
    if(t[p].maxn != 0) ans = {f(t[p].maxn, pos), t[p].maxn};
    if(l == r) return ans;
    int mid = l + r >> 1;
    if(pos <= mid) ans = max(ans, query(t[p].l, l, mid, pos));
    else ans = max(ans, query(t[p].r, mid + 1, r, pos));
    return ans;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    while(n -- )
    {
        int op = read();
        if(op == 0)
        {
            int x = read();
            x = (x + lastans - 1) % mod + 1;
            printf("%d\n", lastans = query(root, 1, mod, x).second);
        }
        else
        {
            int x0 = read(), y0 = read(), x1 = read(), y1 = read();
            x0 = (x0 + lastans - 1) % mod + 1, x1 = (x1 + lastans - 1) % mod + 1;
            y0 = (y0 + lastans - 1) % mod2 + 1, y1 = (y1 + lastans - 1) % mod2 + 1;

            seg t(x0, y0, x1, y1);
            a[++ sid] = t;
            insert(root, 1, mod, t.l, t.r, sid);
        }
    }

    return 0;
}