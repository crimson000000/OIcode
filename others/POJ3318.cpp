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

const int N = 1010;
struct mat
{
    ll a[N][N];
    int n, m;

    mat() {memset(a, 0, sizeof a); n = m = 0; }
    mat(int _n, int _m): n(_n), m(_m)
    {
        memset(a, 0, sizeof a);
    }

    ll * operator [] (int x)
    {
        return a[x];
    }

    mat operator * (const mat& b) const
    {
        mat tmp(n, b.m);
        for(int i = 1; i <= n; i ++ )
            for(int k = 1; k <= m; k ++ )
                for(int j = 1; j <= b.m; j ++ )
                    tmp[i][j] = tmp[i][j] + a[i][k] * b.a[k][j];
        return tmp;
    }

    bool operator == (const mat& b) const
    {
        if(n != b.n || m != b.m) return false;
        for(int i = 1; i <= n; i ++ )   
            for(int j = 1; j <= m; j ++ )
                if(a[i][j] != b.a[i][j])
                    return false;
        return true;
    }
}A, B, C, rnd;
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    srand(time(0));
    n = read();
    A = B = C = mat(n, n);
    for(int i = 1; i <= n; i ++ )   
        for(int j = 1; j <= n; j ++ )
            A[i][j] = read();

    for(int i = 1; i <= n; i ++ )   
        for(int j = 1; j <= n; j ++ )
            B[i][j] = read();

    for(int i = 1; i <= n; i ++ )   
        for(int j = 1; j <= n; j ++ )
            C[i][j] = read();

    rnd = mat(1, n);
    for(int i = 1; i <= n; i ++ ) rnd[1][i] = rand();
    
    auto left = rnd * A * B;
    auto right = rnd * C;

    if(left == right) puts("YES");
    else puts("NO");

    return 0;
}