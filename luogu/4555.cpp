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

const int N = 1e6 + 10;
int f[N];
char s[N], t[N];
int n, len;
int maxl[N];

void manacher(char *t)
{
    s[0] = '@', s[1] = '$';
    for(int i = 1; i <= n; i ++ )
        s[i << 1] = t[i], s[i << 1 | 1] = '$';
    len = n << 1 | 1;
    s[++ len] = '%';

    for(int i = 1, r = 0, mid = 0; i <= len; i ++ )
    {
        if(!(i & 1)) f[i] = 1;
        if(i <= r) f[i] = min(f[2 * mid - i], r - i + 1);
        while(s[i - f[i]] == s[i + f[i]]) f[i] ++;
        if(i + f[i] - 1 > r) mid = i, r = i + f[i] - 1;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", t + 1);
    n = strlen(t + 1);
    manacher(t);

    // cout << s + 1 << endl;

    // for(int i = 1; i < len; i ++ ) cout << f[i] << ' ';
    // puts("");

    memset(maxl, -0x3f, sizeof maxl);

    int lpoint = len - 2;
    for(int i = len - 2; i >= 2; i -- )
    {
        if(i - f[i] + 1 <= lpoint)
        {
            while(lpoint >= i - f[i] + 1 && lpoint != 1)
            {
                maxl[lpoint] = (i - lpoint) + 1;
                lpoint --;
            }
        }
    }

    maxl[1] = maxl[len - 1] = -0x3f3f3f3f;

    int ans = 0;
    for(int i = 2; i < len - 1; i ++ )
    {
        ans = max(ans, f[i] - 1 + maxl[i + f[i]]);
    }

    // for(int i = 1; i < len; i ++ ) cout << maxl[i] << ' ';
    // puts("");

    cout << ans << endl;

    return 0;
}
