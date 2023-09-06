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

const int N = 1e6 + 10;
int a[N];
ll pre[N], suf[N];
int n;

inline void solve()
{
    for(int i = 1; i <= n; i ++ ) pre[i] = suf[i] = 0;
    n = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
    }

    if(n & 1)
    {
        ll ans = 0;
        for(int i = 2; i < n; i += 2)
        {
            if(a[i] <= max(a[i - 1], a[i + 1])) 
                ans += max(a[i - 1], a[i + 1]) - a[i] + 1;
        }
        printf("%lld\n", ans);
        return;
    }
    else
    {
        for(int i = 2; i < n; i ++ )
        {
            pre[i] = pre[i - 2] + max(max(a[i - 1], a[i + 1]) - a[i] + 1, 0);
            // cout << pre[i] << ' ';
        }
        // puts("");
        for(int i = n - 1; i > 1; i -- )
        {
            suf[i] = suf[i + 2] + max(max(a[i - 1], a[i + 1]) - a[i] + 1, 0);
        }
        // for(int i = 2; i < n; i ++ ) cout << suf[i] << ' ';
        // puts("");
        
        ll ans = min(pre[n - 1], pre[n - 2]);
        for(int i = 2; i < n; i ++ )
        {
            if((i + 1) & 1) ans = min(ans, pre[i] + suf[i + 3]);
        }
        printf("%lld\n", ans);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}