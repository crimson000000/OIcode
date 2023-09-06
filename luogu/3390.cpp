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

const int N = 110, mod = 1e9 + 7;
ll a[N][N], res[N][N];
ll n, k;

void mul(ll c[][N], ll a[][N], ll b[][N], int p)
{
    static ll temp[N][N];
    memset(temp, 0, sizeof temp);
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            for(int k = 1; k <= n; k ++ )
                temp[i][j] = (temp[i][j] + a[i][k] * b[k][j] % p) % p;
    
    memcpy(c, temp, sizeof temp);
}

void qmi(ll k, ll p)
{
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            if(i == j) res[i][j] = 1;

    while(k)
    {
        if(k & 1) mul(res, res, a, p);
        mul(a, a, a, p);
        k >>= 1;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n >> k;

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            a[i][j] = read();

    qmi(k, mod);

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= n; j ++ )   
            cout << res[i][j] << ' ';
        puts("");
    }
    
    return 0;
}
