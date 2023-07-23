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

const int N = 1e6 + 10;
struct sol
{
    int l, r, id;
    bool operator < (const sol &a) const
    {
        return l < a.l;
    }
}a[N];
int n, m;
int f[N][22];

inline void init()
{
    for(int i = 1, p = 1; i <= 2 * n; i ++ )
    {
        while(p <= 2 * n && a[i].r >= a[p].l) p ++;
        f[i][0] = p - 1;
    }
    for(int i = 1; i <= 20; i ++ )
        for(int j = 1; j <= 2 * n; j ++ )
            f[j][i] = f[f[j][i - 1]][i - 1];
}

int ans[N];
inline void find(int p)
{
    int lim = a[p].l + m;
    int x = p;
    int res = 0;
    for(int i = 20; i >= 0; i -- )
        if(f[x][i] != 0 && a[f[x][i]].r < lim)
        {
            x = f[x][i];
            res += (1 << i);
        }
    ans[a[p].id] = res + 2;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i].l = read(), a[i].r = read();
        if(a[i].r < a[i].l) a[i].r += m;
        a[i].id = i;
    }

    for(int i = 1; i <= n; i ++ ) 
    {
        a[i + n].l = a[i].l + m;
        a[i + n].r = a[i].r + m;
        a[i + n].id = a[i].id;
    }

    sort(a + 1, a + 2 * n + 1);

    init();

    for(int i = 1; i <= n; i ++ ) find(i);
    for(int i = 1; i <= n; i ++ ) printf("%d ", ans[i]);

    return 0;
}
