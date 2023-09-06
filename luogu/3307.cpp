#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
using i128 = __int128;
#define ll i128
#define int i128

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

inline void write(i128 x)
{
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

typedef pair<ll, ll> PII;
const int N = 1e7 + 10, mod1 = 1e9 + 7;
const ll mod2 = (ll)mod1 * mod1;
ll mod, inv6;
signed miu[N], primes[N], cnt;
bitset<N> st;
ll n, m, k;

inline void init(int n)
{
    miu[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            miu[i] = -1;
        }
        for(int j = 1; j <= cnt && primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] == 0)
            {
                miu[t] = 0;
                break;
            }
            miu[t] = -miu[i];
        }
    }

    for(int i = 1; i <= n; i ++ ) miu[i] += miu[i - 1];
}

inline i128 qmi(i128 a, i128 k, i128 p)
{
    i128 res = 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

const i128 inv61 = qmi(6, mod1 - 2, mod1);
const i128 inv62 = qmi(6, (i128)(mod1 - 1) * mod1 - 1, mod2);

inline i128 f(ll n, ll m)
{
    if(n == 1) return 0;
    if(n == 2) return (i128)m * (m - 1 + mod) % mod;
    m = (m - 1 + mod) % mod;
    i128 res = qmi(m , n, mod);
    if(n & 1) res = (res - m + mod) % mod;
    else res = (res + m) % mod;
    return res;
}

inline vector<PII> divide(ll x)
{
    vector<PII> res;
    res.clear();
    for(ll i = 2; i <= x / i; i ++ )
    {
        if(x % i == 0)
        {
            int cnt = 0;
            while(x % i == 0) x /= i, cnt ++;
            res.emplace_back(i, cnt);
        }
    }
    if(x > 1) res.emplace_back(x, 1);
    return res;
}

inline void dfs(vector<PII> a, vector<PII> &b, int now, PII x)
{
    if(now == a.size()) return b.push_back(x);
    PII tmp = x;
    for(int i = 0; i <= a[now].second; i ++ )
    {
        dfs(a, b, now + 1, tmp);
        if(i) tmp.first *= a[now].first, tmp.second *= a[now].first;
        else tmp.first *= a[now].first, tmp.second *= a[now].first - 1;
    }
}

inline vector<PII> get(ll x)
{
    vector<PII> res;
    res.clear();
    vector<PII> a = divide(x);
    dfs(a, res, 0, {1, 1});
    return res;
}

unordered_map<long long, long long> phi;

inline void solve()
{
    ll res = 0;
    n = read(), k = read();
    if(n % mod1 == 0) mod = mod2, inv6 = inv62;
    else mod = mod1, inv6 = inv61;

    for(int l = 1, r; l <= k; l = r + 1)
    {
        int t = k / l;
        ll g = 2 * t;
        r = k / t;
        g = (g + 3 * t % mod * t % mod) % mod;
        g = (g + t * t % mod * t % mod) % mod;
        g = ((i128)g * inv6 % mod * (miu[r] - miu[l - 1] + mod) % mod) % mod;
        m = (m + g) % mod;
    }

    // write(m);
    // puts("");

    vector<PII> a = get(n);
    for(auto u : a) 
    {
        phi[u.first] = u.second;
        // printf("%lld %lld\n", u.first, u.second);
    }
    for(auto u : a)
        res = (res + f(u.first, m) * phi[n / u.first] % mod) % mod;

    if(n % mod1 == 0) res = ((i128)res / mod1 * qmi(n / mod1, mod1 - 2, mod1)) % mod1;
    else res = res * qmi(n, mod1 - 2, mod1) % mod1;
    write(res);
    puts("");
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(N - 5);

    int T = read();
    while(T -- ) solve();

    return 0;
}
