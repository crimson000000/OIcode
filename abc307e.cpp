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

const int mod = 998244353;
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
ll n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    cout << (qmi(m - 1, n, mod) + ((n & 1) ? mod - 1 : 1) * (m - 1) % mod) % mod << endl;

    return 0;
}