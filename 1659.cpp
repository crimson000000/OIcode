#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;
typedef __int128 i128;

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

const int N = 2e6 + 10, mod = 19930726;
int f[N];
char s[N], t[N];
int cnt[N];
int n;
ll ans;
ll k;

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

void manacher(char *t)
{
    s[0] = '(', s[1] = '$';
    for(int i = 1; i <= n; i ++ )
        s[i << 1] = t[i], s[i << 1 | 1] = '$';
    n = n << 1 | 1;
    s[++ n] = ')';
    for(int i = 1, r = 0, mid = 0; i <= n; i ++ )
    {
        f[i] = 1;
        if(i <= r) f[i] = min(f[2 * mid - i], r - i + 1);
        while(s[i - f[i]] == s[i + f[i]]) f[i] ++;
        if(i + f[i] - 1 > r) r = i + f[i] - 1, mid = i;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    scanf("%s", t + 1);

    manacher(t);
    for(int i = 2; i < n; i += 2) 
    {
        cnt[f[i] - 1] ++;
        // cout << f[i] - 1 << ' ';
    }

    ans = 1;
    for(int i = n; i >= 0; i -- )
    {
        if(cnt[i])
        {
            if(k > cnt[i])
            {
                ans = ans * qmi(i, cnt[i], mod) % mod;
                k -= cnt[i];
                if(i >= 2) cnt[i - 2] += cnt[i];
            }
            else
            {
                ans = ans * qmi(i, k, mod) % mod;
                k = 0;
                break;
            }
        }
    }

    if(k) puts("-1");
    else cout << ans << endl;

    return 0;
}
