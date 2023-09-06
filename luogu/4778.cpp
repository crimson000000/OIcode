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

const int N = 1e6 + 10, mod = 1e9 + 9;
ll fact[N], invfact[N];
int a[N];
int l[N], cnt;
bool vis[N];
int n;

ll qmi(ll a, ll k, ll p)
{
    ll res = 1;
    if(k < 0) return 1;
    while(k)
    {
        if(k & 1) res = res * a % p;
        a = a * a % p;
        k >>= 1;
    }
    return res;
}

void init(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) fact[i] = fact[i - 1] * i % mod;
    invfact[n] = qmi(fact[n], mod - 2, mod);
    for(int i = n - 1; i >= 0; i -- ) invfact[i] = invfact[i + 1] * (i + 1) % mod;
}

void dfs(int now, int x)
{
    if(vis[now]) return;
    vis[now] = true;
    l[x] ++;
    dfs(a[now], x);
}

void solve()
{
    n = read();
    cnt = 0;
    for(int i = 1; i <= n; i ++ ) l[i] = vis[i] = 0;
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
            dfs(i, ++ cnt);
    
    ll ans = fact[n - cnt];
    for(int i = 1; i <= cnt; i ++ )
        ans = ans * qmi(l[i], l[i] - 2, mod) % mod * invfact[l[i] - 1] % mod;

    cout << ans << endl; 
}

int main()
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