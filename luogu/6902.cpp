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
struct sol
{
    int l, r, id;
    bool operator < (const sol &a) const
    {
        return l < a.l;
    }
}a[N];
int b[N];
int n, m;
int f[N][22];

inline void init()
{
    int r = 0;
    for(int i = 1, p = 1; i <= 2 * n; i ++ )
    {
        while(p <= m && a[p].l <= i) 
        {
            r = max(r, a[p].r + 1);
            p ++;
        }
        f[i][0] = r;
    }
    for(int i = 1; i <= 21; i ++ )
        for(int j = 1; j <= 2 * n; j ++ )
            f[j][i] = f[f[j][i - 1]][i - 1];
}

int ans = 0x3f3f3f3f;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ ) 
    {
        a[i].l = read(), a[i].r = read();
        if(a[i].r < a[i].l) a[i].r += n;
        a[i].id = i;
    }

    sort(a + 1, a + m + 1);

    for(int i = 1; i <= 2 * m; i ++ ) 
    {
        b[a[i].l] ++;
        b[a[i].r + 1] --;
    }

    for(int i = 1; i <= 2 * n; i ++ ) b[i] += b[i - 1];
    int cnt = 0;
    bool flag = false;
    for(int i = 1; i <= 2 * n; i ++ )
    {
        if(!b[i]) cnt = 0;
        else cnt ++;
        if(cnt >= n) flag = true;
    }

    if(!flag) 
    {
        puts("impossible");
        return 0;
    }

    init();

    for(int i = 1; i <= 2 * n; i ++ )
    {
        int x = i, res = 0;
        for(int j = 20; j >= 0; j -- )
            if(f[x][j] - i < n)
            {
                x = f[x][j];
                res += (1 << j);
            }
        x = f[x][0];
        res ++;
        if(x - i >= n) ans = min(ans, res);
    }

    if(ans != 0x3f3f3f3f) cout << ans << endl;
    else puts("impossible");

    return 0;
}
