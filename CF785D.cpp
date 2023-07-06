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

const int N = 1e6 + 10, mod = 1e9 + 7;
char s[N];
ll fact[N], invfact[N];
int fr[N], bk[N];
int n;
ll ans;

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

inline void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

inline ll C(int n, int m)
{
    if(n < 0 || m < 0 || n < m) return 0;
    return fact[n] * invfact[n - m] % mod * invfact[m] % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    init(n + n);

    for(int i = 1; i <= n; i ++ )
        if(s[i] == '(')
            fr[i] ++;
        else bk[i] ++;
    
    for(int i = 1; i <= n; i ++ ) fr[i] += fr[i - 1];
    for(int i = n; i; i -- ) bk[i] += bk[i + 1];

    for(int i = 1; i <= n; i ++ )
        if(s[i] == '(')
        {
            ans = (ans + C(fr[i] + bk[i] - 1, fr[i])) % mod;
        }

    cout << ans << endl;

    return 0;
}