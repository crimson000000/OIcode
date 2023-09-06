#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1e5 + 10, INF = 0x3f3f3f3f;
// A max
int f1[N][20];

// A min
int f2[N][20]; 

// A + min
int f3[N][20];

// A - max
int f4[N][20];

// B max
int f5[N][20];

// B min
int f6[N][20];

int lg[N];
int a[N], b[N];
int n, m, q;
int l1, r1, l2, r2;

namespace ljh
{
    inline void BUILD()
    {
        lg[1] = 0;
        for(int i = 2; i <= N - 5; i ++ )
            lg[i] = lg[i >> 1] + 1;

        for(int i = 1; i <= n; i ++ ) f1[i][0] = a[i];
        for(int i = 1; i <= n; i ++ ) f2[i][0] = a[i];
        for(int i = 1; i <= n; i ++ ) f3[i][0] = (a[i] > 0 ? a[i] : INF);
        for(int i = 1; i <= n; i ++ ) f4[i][0] = (a[i] <= 0 ? a[i] : -INF);
        for(int i = 1; i <= m; i ++ ) f5[i][0] = b[i];
        for(int i = 1; i <= m; i ++ ) f6[i][0] = b[i];

        for(int i = 1; i <= 19; i ++ )
            for(int j = 1; j + (1 << i) - 1 <= n; j ++ )
            {
                int k = j + (1 << i - 1);
                f1[j][i] = max(f1[j][i - 1], f1[k][i - 1]);
                f2[j][i] = min(f2[j][i - 1], f2[k][i - 1]);
                f3[j][i] = min(f3[j][i - 1], f3[k][i - 1]);
                f4[j][i] = max(f4[j][i - 1], f4[k][i - 1]);
            }

        for(int i = 1; i <= 19; i ++ )
            for(int j = 1; j + (1 << i) - 1 <= m; j ++ )
            {
                int k = j + (1 << i - 1);
                f5[j][i] = max(f5[j][i - 1], f5[k][i - 1]);
                f6[j][i] = min(f6[j][i - 1], f6[k][i - 1]);
            }
    }

    // A max
    inline int query1(int l, int r)
    {
        int k = lg[r - l + 1];
        return max(f1[l][k], f1[r - (1 << k) + 1][k]);
    }

    // A min
    inline int query2(int l, int r)
    {
        int k = lg[r - l + 1];
        return min(f2[l][k], f2[r - (1 << k) + 1][k]);
    }

    // A + min
    inline int query3(int l, int r)
    {
        int k = lg[r - l + 1];
        return min(f3[l][k], f3[r - (1 << k) + 1][k]);
    }

    // A - min
    inline int query4(int l, int r)
    {
        int k = lg[r - l + 1];
        return max(f4[l][k], f4[r - (1 << k) + 1][k]);
    }

    // B max
    inline int query5(int l, int r)
    {
        int k = lg[r - l + 1];
        return max(f5[l][k], f5[r - (1 << k) + 1][k]);
    }

    // B min
    inline int query6(int l, int r)
    {
        int k = lg[r - l + 1];
        return min(f6[l][k], f6[r - (1 << k) + 1][k]);
    }
}
using namespace ljh;

inline void solve()
{
    ll bmin = query6(l2, r2), bmax = query5(l2, r2);
    // if(bmin >= 0)
    // {
    //     int amax = query1(l1, r1);
    //     printf("%lld\n", (ll)amax * bmin);
    //     return;
    // }
    // if(bmax <= 0)
    // {
    //     int amin = query2(l1, r1);
    //     printf("%lld\n", (ll)amin * bmax);
    //     return;
    // }
    
    ll zamin = query3(l1, r1), zamax = query4(l1, r1);
    ll amax = query1(l1, r1), amin = query2(l1, r1);;
    ll ans = -(ll)INF * INF;
    if(zamin != INF) ans = max(ans, zamin * (zamin >= 0 ? bmin : bmax));
    if(zamax != -INF) ans = max(ans, zamax * (zamax >= 0 ? bmin : bmax));
    ans = max(ans, amax * (amax > 0 ? bmin : bmax));
    ans = max(ans, amin * (amin < 0 ? bmax : bmin));
    printf("%lld\n", ans);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= m; i ++ ) b[i] = read();

    BUILD();

    // cout << query5(2, 2) << endl;

    while(q -- )
    {
        l1 = read(), r1 = read(), l2 = read(), r2 = read();
        solve();
    }

    return 0;
}