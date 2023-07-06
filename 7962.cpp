#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
#define int __int128
#define ll __int128

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

const int N = 1e4 + 10, M = 1e6 + 10;
const ll INF = 1e17;
ll a[N], b[N], s[N], n, maxn;
ll f[2][M];
ll ans = 1e18;
int now, cur;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read(), maxn = max(maxn, a[i]);
    for(int i = 1; i < n; i ++ ) b[i] = a[i + 1] - a[i];

    sort(b + 1, b + n);

    for(int i = 1; i <= n; i ++ ) s[i] = s[i - 1] + b[i];

    memset(f, 0x3f, sizeof f);
    now = 0;
    f[0][0] = 0;

    ll up = maxn * n;

    for(int i = 1; i < n; i ++ )
    {
        if(b[i] == 0) continue;
        now ^= 1;
        for(int j = 0; j <= up; j ++ ) f[now][j] = INF;
        for(int j = 0; j <= up; j ++ )
        {
            if(j + s[i] <= up) f[now][j + s[i]] = min(f[now][j + s[i]], f[now ^ 1][j] + s[i] * s[i]);
            if(j + b[i] * i <= up) f[now][j + b[i] * i] = min(f[now][j + b[i] * i], 
                                    f[now ^ 1][j] + i * b[i] * b[i] + 2ll * b[i] * j);
        }
    }
    
    for(int i = 0; i <= up; i ++ )
        ans = min(ans, n * f[now][i] - i * i);

    cout << (long long)ans << endl;

    return 0;
}