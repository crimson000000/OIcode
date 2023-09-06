#define LOCAL
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 3510, mod = 1e9 + 7;
int f[N][N][2][2];
ll p;
int a;
int n;
char s[N];
ll A[N];
int len = 1;

inline void add(int &a, int b)
{
    a = ((ll)a + b) % mod;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    p = read(), a = read();
    scanf("%s", s + 1);
    n = strlen(s + 1);

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= len; j ++ ) A[j] = A[j] * 10ll;
        A[1] += s[i] - '0';
        for(int j = 1; j <= len; j ++ )
        {
            A[j + 1] += A[j] / p;
            A[j] %= p;
            if(A[len + 1]) len ++;
        }
    }

    // for(int i = 1; i <= len; i ++ ) cout << A[i];
    // puts("");    
    reverse(A + 1, A + len + 1);
    f[0][0][0][0] = 1;
    
    for(int i = 0; i < len; i ++ )
    {
        ll x = A[i + 1];
        for(int j = 0; j <= i; j ++ )
        {
            add(f[i + 1][j][0][0], (x + 1) * f[i][j][0][0] % mod);
            add(f[i + 1][j][1][0], x * (x + 1) / 2 % mod * f[i][j][0][0] % mod);

            add(f[i + 1][j + 1][0][1], x * f[i][j][0][0] % mod);
            add(f[i + 1][j + 1][1][1], x * (x - 1) / 2 % mod * f[i][j][0][0] % mod);

            add(f[i + 1][j][0][0], (p - 1 - x) * f[i][j][0][1] % mod);
            add(f[i + 1][j][1][0], x * (2 * p - 1 - x) / 2 % mod * f[i][j][0][1] % mod);

            add(f[i + 1][j + 1][0][1], (p - x) * f[i][j][0][1] % mod);
            add(f[i + 1][j + 1][1][1], x * (2 * p + 1 - x) / 2 % mod * f[i][j][0][1] % mod);

            add(f[i + 1][j][1][0], p * (p + 1) / 2 % mod * f[i][j][1][0] % mod);
            add(f[i + 1][j + 1][1][1], p * (p - 1) / 2 % mod * f[i][j][1][0] % mod);
            add(f[i + 1][j][1][0], p * (p - 1) / 2 % mod * f[i][j][1][1] % mod);
            add(f[i + 1][j + 1][1][1], p * (p + 1) / 2 % mod * f[i][j][1][1] % mod);
        }
    }

    ll ans = 0;
    for(int i = a; i <= len; i ++ ) ans = (ans + f[len][i][0][0] + f[len][i][1][0]) % mod;
    cout << ans << endl;

    return 0;
}
