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

const int N = 1e6 + 10, mod = 1e9 + 7;
struct seg
{
    int l, r;
    ll sum, add;
}t[N << 2];

inline void pushup(int p)
{
    t[p].sum = (t[p << 1].sum + t[p << 1 | 1].sum) % mod;
}

inline void pushdown(int p)
{
    if(t[p].add)
    {
        t[p << 1].sum = (t[p << 1].sum + t[p].add * (t[p << 1].r - t[p << 1].l + 1) % mod) % mod;
        t[p << 1 | 1].sum = (t[p << 1 | 1].sum + t[p].add * (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) % mod) % mod;
        t[p << 1].add = (t[p << 1].add + t[p].add) % mod;
        t[p << 1 | 1].add = (t[p << 1 | 1].add + t[p].add) % mod;
        t[p].add = 0;
    }
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

inline void change(int p, int l, int r, ll v)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add = (t[p].add + v) % mod;
        t[p].sum = (t[p].sum + (t[p].r - t[p].l + 1) * v % mod) % mod;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, v);
    if(r > mid) change(p << 1 | 1, l, r, v);
    pushup(p);
}

inline ll query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].sum;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    ll sum = 0;
    if(l <= mid) sum = (sum + query(p << 1, l, r)) % mod;
    if(r > mid) sum = (sum + query(p << 1 | 1, l, r)) % mod;
    return sum;
}

int n, m, k;
vector<PII> Add[N], Del[N];
set<PII> seg;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();

    for(int i = 1; i <= k; i ++ )
    {
        int x1 = read(), y1 = read(), x2 = read(), y2 = read();
        Add[x1].emplace_back(y1, y2);
        Del[x2 + 1].emplace_back(y1, y2);
    }

    seg.insert({0, 0});
    for(auto a : Add[1])
        seg.insert(a.first, a.second);

    build(1, 1, m);

    for(int i = 1; i <= n; i ++ )
    {
        sort(Add[i].begin(), Add[i].end());
        reverse(Add[i].begin(), Add[i].end());

        for(auto a : Add[i])
        {
            int x = a.first, y = a.second;
            if(y == m) continue;
            
        }
    }

    return 0;
}