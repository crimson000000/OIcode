#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<long long, long long> PII;

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

const int N = 1e6 + 10, mod = 1e9 + 7, M = 3010;
ll a[N], f[N], t[N];
int n;
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read(), t[a[i]] = i;

    for(int i = n; i; i -- )
    {
        f[i] = 1;
        for(int j = a[i] & (a[i] - 1); j; j = (j - 1) & a[i])
            f[i] = (f[i] + f[t[j]]) % mod;
        ans = (ans + f[i]) % mod;
    }

    ans = (ans - n + mod) % mod;

    cout << ans << endl;

    return 0;
}