#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

ll k, m;
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

ll mul(ll a, ll b, ll p)
{
    ll res = 0;
    while(b)
    {
        if(b & 1) res = (res + a) % p;
        a = a * 2 % p;
        b >>= 1;
    }
    return res;
}

ll bsgs(ll a, ll b, ll p)
{
    ll t = sqrt(p) + 1;
    ll num = 1;
    mp[1] = 0;
    for(int i = 1; i <= t; i ++ ) 
    {
        num = mul(num, a, p);
        mp[mul(num, b, p)] = i;
    }

    ll n = 1;
    for(int i = 1; i <= t; i ++ )
    {
        n = mul(num, n, p);
        if(mp.find(n) != mp.end())
        {
            return i * t - mp[n];
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> k >> m;

    ll a = 10, b = (9 * k + 1) % m, p = m;

    cout << bsgs(a, b, p) << endl;
    
    return 0;
}
