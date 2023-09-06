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

const int N = 2e7 + 10;
int z[N], ext[N];
char a[N], b[N];
int n, m;

inline void getz(char *s, int n)
{
    z[1] = n;
    for(int i = 2, l = 0, r = 0; i <= n; i ++ )
    {
        if(i <= r) z[i] = min(z[i - l + 1], r - i + 1);
        while(i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i] ++;
        if(i + z[i] - 1 > r) r = i + z[i] - 1, l = i;
    }
}

inline void exkmp(char *t, char *s, int n, int m, int *ext)
{
    getz(s, m);
    for(int i = 1, l = 0, r = 0; i <= n; i ++ )
    {
        if(i <= r) ext[i] = min(z[i - l + 1], r - i + 1);
        while(i + ext[i] <= n && t[i + ext[i]] == s[ext[i] + 1]) ext[i] ++;
        if(i + ext[i] - 1 > r) r = i + ext[i] - 1, l = i;
    } 
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1), m = strlen(b + 1);

    exkmp(a, b, n, m, ext);
    
    ll ans1 = 0, ans2 = 0;
    for(int i = 1; i <= m; i ++ ) ans1 ^= (ll)i * (z[i] + 1);
    
    for(int i = 1; i <= n; i ++ ) ans2 ^= (ll)i * (ext[i] + 1);

    cout << ans1 << endl << ans2 << endl;

    return 0;
}
