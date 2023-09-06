#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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

const int N = 2e6 + 10;
#define int ll
int a[N];
int n;
ld sq[N], f[N];

struct node
{
    int p, l, r;
};

node q[N];
int hh, tt;

inline ld w(int j, int i)
{
    return a[j] + sq[i - j];
}

inline int find(int t, int i)
{
    int l = q[t].l, r = q[t].r + 1;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(w(q[t].p, mid) <= w(i, mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

inline void insert(int i)
{
    while(hh <= tt && w(q[tt].p, q[tt].l) <= w(i, q[tt].l)) tt --;
    if(hh > tt)
    {
        tt ++;
        q[tt].l = i, q[tt].r = n, q[tt].p = i;
    }
    else
    {
        int pos = find(tt, i);
        if(pos > n) return;
        q[tt].r = pos - 1;
        tt ++;
        q[tt].l = pos;
        q[tt].r = n;
        q[tt].p = i;
    }
}

inline void solve()
{
    hh = 0, tt = 0;
    q[tt].p = 1, q[tt].l = 1, q[tt].r = n;
    for(int i = 2; i <= n; i ++ )
    {
        while(hh <= tt && q[hh].r < i) hh ++;
        q[hh].l = i;
        f[i] = max(f[i], w(q[hh].p, i));
        insert(i);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        sq[i] = sqrt(i);
    }

    solve();
    reverse(a + 1, a + n + 1);
    reverse(f + 1, f + n + 1);
    solve();

    for(int i = n; i >= 1; i -- )
    {
        cout << max(0ll, int(ceil(f[i])) - a[i]) << endl;
    }

    return 0;
}
