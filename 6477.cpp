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

const int N = 2e6 + 10, mod = 1e9 + 7;
struct node
{
    int l, r;
    ll v, v2;
    ll add;
}t[N << 2];
int lst[N], pre[N];
unordered_map<int, int> mp;
int mptot;
int n, a[N];
ll ans;

inline void pushup(int p)
{
    t[p].v = (t[p << 1].v + t[p << 1 | 1].v) % mod;
    t[p].v2 = (t[p << 1].v2 + t[p << 1 | 1].v2) % mod;
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) return;
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline void tag(int p, int a)
{
    t[p].add = (t[p].add + a) % mod;
    t[p].v2 = (t[p].v2 + 2 * a * t[p].v + a * a * (t[p].r - t[p].l + 1)) % mod;
    t[p].v = (t[p].v + (t[p].r - t[p].l + 1) * a) % mod;
}

inline void pushdown(int p)
{
    if(t[p].add)
    {
        tag(p << 1, t[p].add);
        tag(p << 1 | 1, t[p].add);
        t[p].add = 0;
    }
}

inline void change(int p, int l, int r, int val)
{
    if(l <= t[p].l && t[p].r <= r)
    {
        tag(p, val);
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

inline ll query(int p, int l, int r)
{
    if(l <= t[p].l && t[p].r <= r) return t[p].v2;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    ll ans = 0;
    if(l <= mid) ans = (ans + query(p << 1, l, r)) % mod;
    if(r > mid) ans = (ans + query(p << 1 | 1, l, r)) % mod;
    return ans;
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        if(!mp[a[i]]) mp[a[i]] = ++ mptot;
        a[i] = mp[a[i]];
    }

    build(1, 1, n);

    for(int i = 1; i <= n; i ++ )
    {
        pre[i] = lst[a[i]];
        lst[a[i]] = i;
    }

    for(int r = 1; r <= n; r ++ )
    {
        change(1, pre[r] + 1, r, 1);
        ans = (ans + query(1, 1, r)) % mod;
    }

    cout << ans << endl;
    
    return 0;
}
