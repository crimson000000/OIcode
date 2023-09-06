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

const int N = 3e7 + 10;
int ans, f[N];
char s[N], t[N];
int n;

inline void manacher(char *t)
{
    n = strlen(t + 1);
    s[0] = '#', s[1] = '$';
    for(int i = 1; i <= n; i ++ )
        s[i << 1] = t[i], s[i << 1 | 1] = '$';
    n = n << 1 | 1;
    s[++ n] = ')';

    for(int i = 1, mid = 0, r = 0; i <= n; i ++ )
    {
        f[i] = 1;
        if(i <= r) f[i] = min(f[2 * mid - i], r - i + 1);
        while(s[i - f[i]] == s[i + f[i]]) f[i] ++;
        if(i + f[i] - 1 > r) r = i + f[i] - 1, mid = i;
        ans = max(ans, f[i] - 1);
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", t + 1);
    manacher(t);
    // cout << s + 1 << endl;
    // for(int i = 1; i <= n; i ++ ) cout << f[i] << ' ';
    // puts("");
    cout << ans << endl;

    return 0;
}
