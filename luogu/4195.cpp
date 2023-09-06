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

// struct my_hash {
//   static uint64_t splitmix64(uint64_t x) {
//     x += 0x9e3779b97f4a7c15;
//     x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//     x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//     return x ^ (x >> 31);
//   }

//   size_t operator()(uint64_t x) const {
//     static const uint64_t FIXED_RANDOM =
//         chrono::steady_clock::now().time_since_epoch().count();
//     return splitmix64(x + FIXED_RANDOM);
//   }

//   // 针对 std::pair<int, int> 作为主键类型的哈希函数
//   size_t operator()(pair<uint64_t, uint64_t> x) const {
//     static const uint64_t FIXED_RANDOM =
//         chrono::steady_clock::now().time_since_epoch().count();
//     return splitmix64(x.first + FIXED_RANDOM) ^
//            (splitmix64(x.second + FIXED_RANDOM) >> 1);
//   }
// };

const int N = 1e6 + 10;
ll a, b, p;
map<ll, int> mp;

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

inline ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

inline ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(!b)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}

inline ll Inv(ll a, ll p)
{
    ll x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}

inline ll bsgs(ll a, ll b, ll p)
{
    b %= p, a %= p;
    mp.clear();

    // if(!a)
    // {
    //     if(!b) return 1;
    //     else return -1;
    // }

    int t = ceil(sqrt(p));
    
    ll A = 1;
    for(int i = 0; i < t; i ++, A = A * a % p) 
        mp[b * A % p] = i;
    
    A = qmi(a, t, p);
    ll d = A;
    for(int i = 1; i <= t; i ++, A = A * d % p)
    {
        if(mp.find(A) != mp.end() && i * t - mp[A] >= 0)
        {
            return i * t - mp[A];
        }
    }
    return -1;
}

inline ll exbsgs(ll a, ll b, ll p)
{
    if(b == 1 || p == 1) return 0;
    ll g = gcd(a, p);
    ll k = 0, na = 1;
    while(g != 1)
    {
        if(b % g != 0) return -1;
        k ++;
        b /= g, p /= g;
        na = na * (a / g) % p;
        if(na == b) return k;
        g = gcd(a, p);
    }
    ll f = bsgs(a, b * Inv(na, p) % p, p);
    if(f == -1) return -1;
    return (f + k);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    while(1)
    {
        a = read(), p = read(), b = read();
        if(!a && !p && !b) return 0;
        a %= p, b %= p;
        ll t = exbsgs(a, b, p);
        if(t == -1) puts("No Solution");
        else printf("%lld\n", t);
    }

    return 0;
}
