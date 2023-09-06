#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll, int> PII;

// #define int ll

#define y1 _y1

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

const int N = 2010;
int a[N][N], h[N][N], l[N][N], r[N][N];
ll s[N][N];
int n, k;
ll maxn;

inline ll getsum(int x1, int y1, int x2, int y2)
{
    assert(y1 > 0);
    assert(x1 > 0);
    return s[x2][y2] - s[x1 - 1][y2] - s[x2][y1 - 1] + s[x1 - 1][y1 - 1];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    k = read(), n = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            int x = read();
            a[i][j] = x;

            if(x >= k && x <= 2 * k)
            {
                printf("%d %d %d %d\n", j, i, j, i);
                exit(0);
            }

            if(x > 2 * k) continue;
            r[i][j] = l[i][j] = j;
            h[i][j] = 1;
        }

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            s[i][j] = (ll)a[i][j] - s[i - 1][j - 1] + s[i - 1][j] + s[i][j - 1];

    for(int i = 1; i <= n; i ++ )
        for(int j = 2; j <= n; j ++ )
            if(a[i][j] < k && a[i][j - 1] < k)
                l[i][j] = l[i][j - 1];

    for(int i = 1; i <= n; i ++ )
        for(int j = n - 1; j; j -- )
            if(a[i][j] < k && a[i][j + 1] < k)
                r[i][j] = r[i][j + 1];

    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            if(i > 1 && a[i][j] < k && a[i - 1][j] < k)
            {
                l[i][j] = max(l[i - 1][j], l[i][j]);
                r[i][j] = min(r[i - 1][j], r[i][j]);
                h[i][j] = h[i - 1][j] + 1;
            }

    // cout << h[4][4] << endl;

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            if(a[i][j] < k && getsum(i - h[i][j] + 1, l[i][j], i, r[i][j]) >= k)
            {
                y1 = l[i][j];
                y2 = r[i][j];
                x1 = i - h[i][j] + 1;
                x2 = i;
                break;
            }

    if(x1 == 0)
    {
        puts("NIE");
        return 0;
    }

    maxn = getsum(x1, y1, x2, y2);
    if(maxn < k) 
    {
        puts("NIE");
        return 0;
    }

    if(maxn >= k && maxn <= k * 2)
    {
        printf("%d %d %d %d\n", y1, x1, y2, x2);
        return 0;
    }

    for(int i = x2; i >= x1; i -- )
    {
        ll now = getsum(i, y1, i, y2);
        if(now >= k && now <= 2 * k)
        {
            printf("%d %d %d %d\n", y1, i, y2, i);
            return 0;
        }
        if(now > 2 * k)
        {
            maxn = now;
            for(int j = y2; j >= y1; j -- )
            {
                maxn -= a[i][j];
                if(maxn >= k && maxn <= 2 * k)
                {
                    printf("%d %d %d %d\n", y1, i, j - 1, i);
                    return 0;
                }
            }
        }
        else
        {
            maxn -= now;
            if(maxn >= k && maxn <= k * 2)
            {
                printf("%d %d %d %d\n", y1, x1, y2, i - 1);
                return 0;
            }
        }
    }

    return 0;
}