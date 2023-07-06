#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int mod = 1e9 + 7, sqrt2 = 59713600;

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
        x = ((x << 3) + (x << 1) + ch - '0') % (mod - 1);
        ch = getchar();
    }
    return x * f;
}

ll qmi(ll a, ll k, ll p)
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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    ll n = read();

    cout << qmi(4, mod - 2, mod) * sqrt2 % mod * (qmi(1 + sqrt2, n, mod) - qmi(1 - sqrt2 + mod, n, mod) + mod) % mod << endl;

    return 0;
}