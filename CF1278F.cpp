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

const int N = 5010, mod = 998244353;
int S[N][N];
ll n, m, k, ans;

inline ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

inline void init(int n)
{
    S[0][0] = 1;
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= i; j ++ )
            S[i][j] = (S[i - 1][j - 1] + (ll)j * S[i - 1][j] % mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    init(k);

    ll fct = 1;
    for(int i = 0; i <= k; i ++ )
    {
        ans = (ans + S[k][i] * fct % mod * qmi(qmi(m, i, mod), mod - 2, mod) % mod) % mod;
        fct = fct * (n - i) % mod;
    }

    cout << ans << endl;

    return 0;
}