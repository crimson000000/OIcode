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
int a[N];
int n, m, q;
struct node
{
    int l, r;
    int k, L;
    ll num;
    
    node operator + (const node& b) const
    {
        if(!b.k && !b.L) return *this;
        if(!k && !L) return b;
        node ans;
        if(L > b.k)
        {
            ans.k = k;
            ans.L = L - b.k + b.L;
            ans.num = ((num >> b.k) << b.L) + b.num;
        }
        else
        {
            ans.k = k + b.k - L;
            ans.L = b.L;
            ans.num = b.num;
        }
        return ans;
    }
}t[N << 2];

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        a[l] = read();
        if(a[l] == 1) t[p].L = 1;
        if(a[l] == 2) t[p].L = 1, t[p].num = 1;
        if(a[l] == 3) t[p].k = 1;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

void change(int p, int pos, int val)
{
    if(t[p].l == t[p].r)
    {
        t[p].L = t[p].num = t[p].k = 0;
        if(val == 1) t[p].L = 1;
        if(val == 2) t[p].L = 1, t[p].num = 1;
        if(val == 3) t[p].k = 1;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(pos <= mid) change(p << 1, pos, val);
    else change(p << 1 | 1, pos, val);
    t[p] = t[p << 1] + t[p << 1 | 1];
}

node query(int p, int l, int r)
{
    if(t[p].r < l || t[p].l > r) return {0, 0, 0, 0, 0};
    if(t[p].l >= l && t[p].r <= r) return t[p];
    node ans = {t[p].l, t[p].r, 0, 0, 0};
    node lans, rans;
    lans = query(p << 1, l, r);
    rans = query(p << 1 | 1, l, r);
    ans = lans + rans;
    return ans;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read();

    build(1, 1, m);

    while(q -- )
    {
        int op = read();
        if(op == 1)
        {
            ll s = read();
            int l = read(), r = read();
            auto ans = query(1, l, r);
            printf("%lld\n", (max(1ll, s >> ans.k) << ans.L) + ans.num);
        }
        else
        {
            int x = read(), y = read();
            change(1, x, y);
        }
    }

    return 0;
}