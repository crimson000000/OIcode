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

const int N = 3010;
int n, k;
int a[N];
int maxn;
int ans;

inline void solve()
{
    maxn = 0;
    ans = 0x3f3f3f3f;
    n = read(), k = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        maxn = max(maxn, a[i]);
    }

    for(int i = maxn / k; i <= maxn; i ++ )
    {
        int minn = 0x3f3f3f3f;
        // cout << i << ':';
        for(int j = 1; j <= n; j ++ )
        {
            int l = 1, r = k;
            while(l < r)
            {
                int mid = l + r >> 1;
                if(a[j] / mid <= i) r = mid;
                else l = mid + 1;
            }
            
            // cout << l << ' ';
            minn = min(minn, a[j] / l);
        }
        // puts("");
        ans = min(ans, i - minn);
    }
    printf("%d\n", ans);
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