#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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
ll d[N], tot;
ll f[N], cnt[N];
int fa[N], siz[N];
int n;
double k;
vector<ll> nums;

struct node
{
    int l, r;
    ll minn, add;
}t[N << 2];

inline void pushup(int p)
{
    t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
}

inline void pushdown(int p)
{
    if(t[p].add)
    {
        t[p << 1].add += t[p].add;
        t[p << 1 | 1].add += t[p].add;
        t[p << 1].minn += t[p].add;
        t[p << 1 | 1].minn += t[p].add;
        t[p].add = 0;
    }
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].minn = f[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void change(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add += val;
        t[p].minn += val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

inline int find(int p, int val)
{
    pushdown(p);
    if(t[p].l == t[p].r) 
    {
        if(t[p].minn >= val) return t[p].l;
        else return t[p].l - 1;
    }
    if(t[p << 1].minn >= val) return find(p << 1 | 1, val);
    return find(p << 1, val);
}

bitset<N> done;
int ans[N];
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), scanf("%lf", &k);
    for(int i = 1; i <= n; i ++ ) 
    {
        d[i] = read();
        nums.emplace_back(d[i]);
        fa[i] = i / k;
        siz[i] = 1;
    }

    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n; i ++ )
        d[i] = lower_bound(nums.begin(), nums.end(), d[i]) - nums.begin() + 1;

    for(int i = 1; i <= n; i ++ ) cnt[d[i]] ++;
    for(int i = n; i >= 1; i -- ) 
    {
        f[i] = f[i + 1] + cnt[i];
        siz[fa[i]] += siz[i];
    }

    build(1, 1, n);

    for(int i = 1; i <= n; i ++ )
    {
        if(fa[i] && !done[fa[i]]) change(1, 1, ans[fa[i]], siz[fa[i]] - 1);
        done[fa[i]] = true;
        int pos = find(1, siz[i]);
        ans[i] = pos;
        change(1, 1, ans[i], -siz[i]);
        cout << nums[pos - 1] << ' ';
    }
    
    return 0;
}