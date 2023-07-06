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

const int N = 1010, INF = 0x3f3f3f3f;
int f[N][N], c[N][N], g[N][N];
int s[N][N];
int nums[N];
struct activity
{
    int l, r;
}a[N];

int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int s = read(), t = read();
        t += s - 1;
        a[i] = {s, t};
        nums[++ m] = s;
        nums[++ m] = t;
    }

    sort(nums + 1, nums + m + 1);

    for(int i = 1; i <= n; i ++ ) 
    {
        a[i].l = lower_bound(nums + 1, nums + m + 1, a[i].l) - nums + 1;
        a[i].r = lower_bound(nums + 1, nums + m + 1, a[i].r) - nums + 1;
    }

    m += 2;

    for(int l = 1; l <= m; l ++ )
        for(int r = l; r <= m; r ++ )
            for(int i = 1; i <= n; i ++ )
                if(l <= a[i].l && a[i].r <= r)
                    c[l][r] ++;

    for(int i = 0; i <= m + 1; i ++ )
        for(int j = 0; j <= n; j ++ )
            f[i][j] = g[i][j] = -INF;

    f[0][0] = 0, g[m + 1][0] = 0;
    for(int i = 1; i <= m; i ++ )
        for(int j = 0; j <= n; j ++ )
            for(int k = 0; k <= i - 1; k ++ )
            {
                if(j >= c[k + 1][i]) f[i][j] = max(f[i][j], f[k][j - c[k + 1][i]]);
                f[i][j] = max(f[i][j], f[k][j] + c[k + 1][i]);
            }

    int ___ = 0;
    for(int i = 0; i <= n; i ++ ) 
        ___ = max(___, min(f[m][i], i));

    cout << ___ << endl;
    
    for(int i = m; i; i -- )
        for(int j = 0; j <= n; j ++ )
            for(int k = i + 1; k <= m + 1; k ++ )
            {
                if(j >= c[i][k - 1]) g[i][j] = max(g[i][j], g[k][j - c[i][k - 1]]);
                g[i][j] = max(g[i][j], g[k][j] + c[i][k - 1]);
            }
    
    for (int i = 1; i <= m; i ++ ) 
    {
		for (int j = n - 1; j >= 0; j -- ) 
        {
			f[i][j] = max(f[i][j], f[i][j + 1]);
            g[i][j] = max(g[i][j], g[i][j + 1]);
		}
	}
    
    // for(int i = 1; i <= m; i ++ )
    // {
    //     for(int j = 0; j <= n; j ++ )
    //     {
    //         printf("%d ", g[i][j]);
    //     }
    //     puts("");
    // }

    for(int l = 1; l <= m; l ++ )
        for(int r = l + 2; r <= m; r ++ )
        {
            s[l][r] = -INF;
            for(int k = 0, t = n; k <= n; k ++ )   
            {
                if(f[l][k] < 0) break;
                while(t >= 0)
                {
                    int tmp = min(f[l][k] + g[r][t], k + t + c[l + 1][r - 1]);
                    if(tmp >= s[l][r]) s[l][r] = tmp;
                    else break;
                    t --;
                }
                t ++;
            }
        }

    for(int u = 1; u <= n; u ++ )
    {
        int ans = 0;
        for(int i = 1; i <= a[u].l - 1; i ++ )
            for(int j = a[u].r + 1; j <= m; j ++ )
                ans = max(ans, s[i][j]);
        printf("%d\n", ans);
    }

    return 0;
}