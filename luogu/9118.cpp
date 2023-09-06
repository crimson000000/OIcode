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

const int N = 110;
int k;
ll n;
ll f[N];
ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();

    for(int i = 64; i >= k; i -- )
    {
        f[i] = floor(pow<long double>(n, 1.0 / i)) - 1;
        for(int j = i * 2; j <= 64; j += i)
            f[i] -= f[j];
        ans += f[i];
    }

    cout << ans + 1 << endl;

    return 0;
}