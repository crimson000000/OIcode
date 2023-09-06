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

const int N = 2010, mod = 1e9 + 7;
char s[N];
int n;
int tot[N];
double f[N], a[N], b[N];
double ans;

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

ll inv(ll x)
{
    return qmi(x, mod - 2, mod);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s);
    n = strlen(s);
    for(int i = 0; i < n; i ++ ) tot[s[i] - 'A'] ++;

    a[1] = -1, b[1] = 0.5 * n;
    for(int i = 2; i < n; i ++ )
    {
        double inv = 0.5 / i, p = 1 - (1 - i) * inv * a[i - 1];
        a[i] = (-1 - i) * inv / p;
        b[i] = (n * (n - 1) * inv / (n - i) - (1 - i) * inv * b[i - 1]) / p;
    }

    for(int i = n - 1; i; i -- ) f[i] = b[i] - a[i] * f[i + 1];
    for(int i = 0; i < 26; i ++ ) ans += 1.0 * tot[i] / n * f[tot[i]];

    printf("%.1lf\n", ans);
    
    return 0;
}
