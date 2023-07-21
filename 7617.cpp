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
ll a[N], cnt[N];
int n;
ll ans;

inline void work(ll x)
{
    ll res = 0;
    while(x) res |= (1 << (x % 10)), x /= 10;
    cnt[res] ++;
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
        work(a[i]);
    }

    for(int i = 1; i < (1 << 10); i ++ )
        for(int j = i + 1; j < (1 << 10); j ++ )
            if((i & j) != 0)
                ans += cnt[i] * cnt[j];
    
    for(int i = 1; i < (1 << 10); i ++ )
        ans += cnt[i] * (cnt[i] - 1) / 2;

    cout << ans << endl;

    return 0;
}
