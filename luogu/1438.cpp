#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int long long
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
struct segment
{
    int l, r;
    int sum, add;
}t[N << 2];
int a[N];
int n, m;

inline void pushup(int p)
{
    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
}

inline void pushdown(int p)
{
    if(t[p].add)
    {
        int &add = t[p].add;
        t[p << 1].sum += (t[p << 1].r - t[p << 1].l + 1) * add;
        t[p << 1 | 1].sum += (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) * add;
        t[p << 1].add += add;
        t[p << 1 | 1].add += add;
        add = 0;
    }
}

void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r)
    {
        t[p].sum = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

void change(int p, int l, int r, int val)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].add += val;
        t[p].sum += (t[p].r - t[p].l + 1) * val;
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) change(p << 1, l, r, val);
    if(r > mid) change(p << 1 | 1, l, r, val);
    pushup(p);
}

int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        return t[p].sum;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    int sum = 0;
    if(l <= mid) sum += query(p << 1, l, r);
    if(r > mid) sum += query(p << 1 | 1, l, r);
    return sum;
}

void add_ap(int l, int r, int k, int d)
{
    change(1, l, l, k);
    if(l + 1 <= n) change(1, l + 1, r, d);
    int plus = (r - l) * d + k;
    if(r + 1 <= n) change(1, r + 1, r + 1, -plus);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = n; i >= 1; i -- )
        a[i] = a[i] - a[i - 1];

    build(1, 1, N - 1);

    while(m -- )
    {
        int op = read();
        if(op == 1)
        {
            int l = read(), r = read(), k = read(), d = read();
            add_ap(l, r, k, d);
        }
        else
        {
            int p = read();
            cout << query(1, 1, p) << endl;
        }
    }
    
    return 0;
}
