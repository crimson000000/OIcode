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

const int N = 110;
struct mat
{
    ll a[N][N];
    int n, m;

    mat() {memset(a, 0, sizeof a); }
    mat(int n, int m): n(n), m(m) {memset(a, 0, sizeof a);}

    ll * operator [] (const int x)
    {
        return a[x];
    }

    mat operator * (const mat& b) const
    {
        mat res(n, b.m);
        for(int i = 1; i <= n; i ++ )
            for(int k = 1; k <= m; k ++ )
                for(int j = 1; j <= b.m; j ++ )
                    res[i][j] ^= a[i][k] * b.a[k][j];
        return res;
    }
}B[40], F, A;
int n, m, q;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read();
    B[0] = mat(n, n);
    A = mat(1, n);

    for(int i = 1; i <= n; i ++ ) A[1][i] = read();

    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        B[0][a][b] = B[0][b][a] = 1;
    }

    for(int i = 1; i <= 32; i ++ ) B[i] = B[i - 1] * B[i - 1];

    while(q -- )
    {
        ll a = read();
        F = A;
        for(int i = 32; i >= 0; i -- )
            if(a >> i & 1)
                F = F * B[i];
        
        printf("%lld\n", F[1][1]);
    }

    return 0;
}