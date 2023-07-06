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

const int N = 150;
struct egg
{
    int x, y, v;
    bool st;
    bool operator < (const egg& W) const 
    {
        return x < W.x;
    }
}e[N];
vector<int> nums;
int n, m;
int f[N][N][3];
int sum[N];
int Y;

inline void readin()
{
    n = read(), m = read();
    nums.push_back(m);

    e[n + 1].x = m;
    e[n + 1].st = true;
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%lld", &e[i].x);
        nums.push_back(e[i].x);
        e[i].st = false;
    }

    for(int i = 1; i <= n; i ++ ) 
    {
        scanf("%lld", &e[i].y);
        Y += e[i].y;
    }

    for(int i = 1; i <= n; i ++ ) scanf("%lld", &e[i].v);
}

inline void discrete()
{
    sort(nums.begin(), nums.end());
    nums.erase(unique(nums.begin(), nums.end()), nums.end());

    for(int i = 1; i <= n + 1; i ++ )
        e[i].x = lower_bound(nums.begin(), nums.end(), e[i].x) - nums.begin() + 1;
}

inline int get(int x)
{
    return nums[x - 1];
}

inline int getsum(int l, int r)
{
    return sum[r] - sum[l - 1];
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    readin();
    
    // discrete();

    sort(e + 1, e + n + 2);

    for(int i = 1; i <= n + 1; i ++ )
    {
        sum[i] = sum[i - 1] + e[i].v;
    }
    
    n += 1;
    memset(f, 0x3f, sizeof f);
    // for(int i = 1; i <= n; i ++ ) printf("%d: %d\n", e[i].x, get(e[i].x));

    for(int i = 1; i <= n; i ++ )
        if(e[i].st)
        {
            f[i][i][0] = f[i][i][1] = 0;
        }

    for(int len = 2; len <= n; len ++ )
    {
        for(int l = 1; l <= n; l ++ )
        {
            int r = l + len - 1;
            if(r > n) break;
            // f[l][r][0] = min(f[l][r][0], f[l + 1][r][0] + (get(l + 1) - get(l)) * (sum[n] - getsum(l + 1, r)));
            // f[l][r][0] = min(f[l][r][0], f[l + 1][r][1] + (get(r) - get(l)) * (sum[n] - getsum(l + 1, r)));
            // f[l][r][1] = min(f[l][r][1], f[l][r - 1][1] + (get(r) - get(r - 1)) * (sum[n] - getsum(l, r - 1)));
            // f[l][r][1] = min(f[l][r][1], f[l][r - 1][0] + (get(r) - get(l)) * (sum[n] - getsum(l, r - 1)));
            // printf("%d: %d\n", r - 1, get(r - 1));
            f[l][r][0] = min(f[l][r][0], f[l + 1][r][0] + (e[l + 1].x - e[l].x) * (sum[n] - getsum(l + 1, r)));
            f[l][r][0] = min(f[l][r][0], f[l + 1][r][1] + (e[r].x - e[l].x) * (sum[n] - getsum(l + 1, r)));
            f[l][r][1] = min(f[l][r][1], f[l][r - 1][1] + (e[r].x - e[r - 1].x) * (sum[n] - getsum(l, r - 1)));
            f[l][r][1] = min(f[l][r][1], f[l][r - 1][0] + (e[r].x - e[l].x) * (sum[n] - getsum(l, r - 1)));
        }
    }

    double ans = Y - min(f[1][n][1], f[1][n][0]);
    printf("%.3lf\n", ans / 1000);
    
    return 0;
}

