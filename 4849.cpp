#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;

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

const int N = 1e6 + 10, mod = 998244353;
struct ele
{
    int a, b, c, d;
    int ok;
    int id;
    ll w, ans, cnt;
}e[N], tmp[N];
int top = 1;
int pos1[N], pos2[N];
vector<int> nums;

int n, m;

inline bool cmpa(ele a, ele b)
{
    if(a.a != b.a) return a.a < b.a;
    if(a.b != b.b) return a.b < b.b;
    if(a.c != b.c) return a.c < b.c;
    return a.d < b.d;
}

inline bool cmpb(ele a, ele b)
{
    if(a.b != b.b) return a.b < b.b;
    if(a.a != b.a) return a.a < b.a;
    if(a.c != b.c) return a.c < b.c;
    return a.d < b.d;
}

inline bool cmpc(ele a, ele b)
{
    return a.c < b.c;
}

namespace sgm
{
    struct node
    {
        int l, r;
        ll cnt, f;
    }t[N << 2];

    inline void pushup(int p)
    {
        t[p].f = max(t[p << 1].f, t[p << 1 | 1].f);
        t[p].cnt = 0;
        if(t[p << 1].f == t[p].f) t[p].cnt = (t[p].cnt + t[p << 1].cnt) % mod;
        if(t[p << 1 | 1].f == t[p].f) t[p].cnt = (t[p].cnt + t[p << 1 | 1].cnt) % mod;
    }
    
    inline void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) return;
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    inline void change(int p, int pos, ll val, ll cnt)
    {
        if(t[p].l == t[p].r)
        {
            if(val > t[p].f) t[p].f = val, t[p].cnt = cnt;
            else if(val == t[p].f) t[p].cnt = (t[p].cnt + cnt) % mod;
            return;
        }
        int mid = t[p].l + t[p].r >> 1;
        if(pos <= mid) change(p << 1, pos, val, cnt);
        else change(p << 1 | 1, pos, val, cnt);
        pushup(p);
    }

    inline ll query(int p, int l, int r, ll &cnt)
    {
        if(t[p].l >= l && t[p].r <= r)
        {
            cnt = t[p].cnt;
            return t[p].f;
        }
        int mid = t[p].l + t[p].r >> 1;
        ll lans = 0, rans = 0;
        ll lcnt = 0, rcnt = 0;
        if(l <= mid) lans = query(p << 1, l, r, lcnt);
        if(r > mid) rans = query(p << 1 | 1, l, r, rcnt);
        ll ans = max(lans, rans);
        if(lans == ans) cnt = (cnt + lcnt) % mod;
        if(rans == ans) cnt = (cnt + rcnt) % mod;
        return ans;
    }

    inline void clear(int p, int pos)
    {
        t[p].cnt = t[p].f = 0;
        if(t[p].l == t[p].r) return;
        int mid = t[p].l + t[p].r >> 1;
        if(pos <= mid) clear(p << 1, pos);
        else clear(p << 1 | 1, pos);
    }
}

inline void cdq2(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq2(l, mid);
    
    sort(e + l, e + mid + 1, cmpc);
    sort(e + mid + 1, e + r + 1, cmpc);
    int i = l;
    for(int j = mid + 1; j <= r; j ++ )
    {
        while(i <= mid && e[i].c <= e[j].c)
        {
            if(e[i].ok) sgm::change(1, e[i].d, e[i].ans, e[i].cnt);
            i ++;
        }
        if(!e[j].ok)
        {
            ll cnt = 0, nans = 0;
            nans = sgm::query(1, 1, e[j].d, cnt);
            if(e[j].ans < nans + e[j].w)
            {
                e[j].ans = nans + e[j].w;
                e[j].cnt = cnt;
            }
            else if(e[j].ans == nans + e[j].w)
            {
                e[j].cnt = (e[j].cnt + cnt) % mod;
            }
        }
    }

    for(int j = l; j < i; j ++ ) sgm::clear(1, e[j].d);
    for(int i = l; i <= r; i ++ ) tmp[pos2[e[i].id]] = e[i];
    for(int i = l; i <= r; i ++ ) e[i] = tmp[i];
    cdq2(mid + 1, r);
}

inline void cdq1(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    cdq1(l, mid);

    for(int i = l; i <= mid; i ++ ) e[i].ok = true;
    for(int i = mid + 1; i <= r; i ++ ) e[i].ok = false;

    sort(e + l, e + r + 1, cmpb);
    for(int i = l; i <= r; i ++ ) pos2[e[i].id] = i;
    
    cdq2(l, r);

    for(int i = l; i <= r; i ++ ) tmp[pos1[e[i].id]] = e[i];
    for(int i = l; i <= r; i ++ ) e[i] = tmp[i];
    cdq1(mid + 1, r);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\noip\\in.in", "r", stdin);
        freopen("D:\\noip\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        int a = read(), b = read(), c = read(), d = read(), w = read();
        e[i].a = a, e[i].b = b, e[i].c = c, e[i].d = d;
        e[i].w = w;
        nums.emplace_back(d);
    }

    sgm::build(1, 1, n);

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
    {
        e[i].d = lower_bound(nums.begin(), nums.end(), e[i].d) - nums.begin() + 1;
    }

    sort(e + 1, e + n + 1, cmpa);
    for(int i = 2; i <= n; i ++ )
    {
        if(e[i].a != e[i - 1].a || e[i].b != e[i - 1].b || e[i].c != e[i - 1].c || e[i].d != e[i - 1].d)
            e[++ top] = e[i];
        else e[top].w += e[i].w;           
    }

    for(int i = 1; i <= top; i ++ )
    {
        e[i].id = i;
        e[i].ans = e[i].w;
        e[i].cnt = 1;
        pos1[e[i].id] = i;
    }

    cdq1(1, top);

    ll ans = 0, cnt = 0;
    for(int i = 1; i <= top; i ++ ) ans = max(ans, e[i].ans);
    for(int i = 1; i <= top; i ++ )
        if(e[i].ans == ans)
            cnt = (cnt + e[i].cnt) % mod;
    
    printf("%lld\n%lld\n", ans, cnt);

    return 0;
}
