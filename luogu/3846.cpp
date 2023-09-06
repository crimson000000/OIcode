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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

ll p, b, n;
unordered_map<ll, ll> mp;

ll qmi(ll a, ll b, ll p)
{
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    p = read(), b = read(), n = read();
    ll t = sqrt(p) + 1;

    for(int i = 0; i < t; i ++ ) mp[n * qmi(b, i, p) % p] = i;

    if(b == 0)
    {
        if(n == 0) 
        {
            puts("1");
            return 0;
        }
        else
        {
            puts("no solution");
            return 0;
        }
    }

    for(int i = 1; i <= t; i ++ )
    {
        ll c = qmi(b, i * t, p);
        if(mp.find(c) != mp.end())
        {
            if(mp[c] >= 0 && i * t - mp[c] >= 0)
            {
                cout << i * t - mp[c] << endl;
                return 0;
            }
        }
    }

    puts("no solution");

    return 0;
}
