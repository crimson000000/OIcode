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

const int N = 1e5 + 10, B = 300, M = 30000000;
int t[N * B + N];
int a[N];
int n;
int ans;

int solve()
{
    int res = 0;
    for(int d = 0; d <= B; d ++ )
    {
        int cnt = 0;
        for(int i = 1; i <= n; i ++ ) 
        {
            t[a[i] - i * d + M] ++;
            cnt = max(cnt, t[a[i] - i * d + M]);
        }
        for(int i = 1; i <= n; i ++ ) t[a[i] - i * d + M] = 0;
        res = max(res, cnt);
    }
    for(int i = 1; i <= n; i ++ )
    {
        int cnt = 0;
        for(int j = i + 1; j <= n && B * (j - i) <= 100000; j ++ )
        {
            if((a[i] - a[j]) % (i - j) == 0) 
            {
                t[(a[i] - a[j]) / (i - j) + N] ++;
                cnt = max(cnt, t[(a[i] - a[j]) / (i - j) + N]);
            }
        }
        for(int j = i + 1; j <= n && B * (j - i) <= 100000; j ++ )
        {
            if((a[i] - a[j]) % (i - j) == 0) 
                t[(a[i] - a[j]) / (i - j) + N] = 0;
        }
        res = max(res, ++ cnt);
    }
    return n - res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    ans = solve();
    reverse(a + 1, a + n + 1);
    ans = min(ans, solve());

    cout << ans << endl;   

    return 0;
}