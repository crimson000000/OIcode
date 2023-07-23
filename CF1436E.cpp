#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2e6 + 10;
int a[N];
int n;
bitset<N> vis;

struct seg
{
    int l, r;
    int minn;
}t[N];
int lst[N];

inline void pushup(int p)
{
    t[p].minn = min(t[p << 1].minn, t[p << 1 | 1].minn);
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    if(l == r) 
    {
        t[p].minn = 0;
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

inline void change(int p, int pos, int v)
{
    if(t[p].l == t[p].r)
    {
        t[p].minn = v;
        return;
    }
    int mid = t[p].l + t[p].r >> 1;
    if(pos <= mid) change(p << 1, pos, v);
    else change(p << 1 | 1, pos, v);
    pushup(p);
    return;
}

inline int query(int p, int l, int r)
{
    if(t[p].l >= l && t[p].r <= r) return t[p].minn;
    int mid = t[p].l + t[p].r >> 1;
    int res = 0x3f3f3f3f;
    if(l <= mid) res = min(res, query(p << 1, l, r));
    if(r > mid) res = min(res, query(p << 1 | 1, l, r));
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    build(1, 1, n);
    
    for(int i = 1; i <= n; i ++ )
    {
        if(a[i] != 1) vis[1] = true;
        if(a[i] > 1 && query(1, 1, a[i] - 1) > lst[a[i]]) vis[a[i]] = true;
        lst[a[i]] = i;
        change(1, a[i], i); 
    }

    for(int i = 2; i <= n + 1; i ++ ) 
        if(query(1, 1, i - 1) > lst[i])
            vis[i] = true;

    for(int i = 1; i <= n + 1; i ++ )
        if(!vis[i])
        {
            cout << i << endl;
            return 0;
        }

    cout << n + 2 << endl;

    return 0;
}
