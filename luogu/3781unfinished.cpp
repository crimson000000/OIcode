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
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 5e4 + 10, mod = 10007, M = 130;
int h[N], e[N << 1], ne[N << 1], idx;
int inv[M];
int n, m, Q;

inline void FWT(int a[], int opt = 1)
{
    for(int up = 2; up <= m; up <<= 1)
        for(int k = 0; k < m; k += up)
            for(int j = 0; j < up; j ++ )
            {
                a[j + k] = (a[j + k] + a[j + k + up / 2]) % mod;
                a[j + k + up / 2] = (a[j + k] - 2 * a[j + k + up / 2] % mod + mod) % mod;
                a[j + k] = a[j + k] * opt % mod;
                a[j + k + up / 2] = a[j + k + up / 2] * opt % mod;
            }
}

struct poly
{
    int a[M];
    poly() {memset(a, 0, sizeof a);}

    inline int& operator [] (int x)
    {
        return a[x];
    } 

    inline poly operator + (const poly b) const
    {
        poly res;
        for(int i = 0; i < m; i ++ ) res[i] = (a[i] + b[i]) % mod;
        return res;
    }

    inline poly operator - (const poly b) const
    {
        poly res;
        for(int i = 0; i < m; i ++ ) res[i] = (a[i] - b[i] + mod) % mod;
        return res;
    }
    
    inline poly operator * (const poly b) const
    {
        poly res;
        for(int i = 0; i < m; i ++ ) res[i] = (a[i] * b[i]) % mod;
        return res;
    }

    inline poly operator / (const poly b) const
    {
        poly res;
        for(int i = 0; i < m; i ++ ) res[i] = (a[i] * inv[b[i]]) % mod;
        return res;
    }
};

struct matrix
{
    poly a[2][2];
    inline poly* operator [] (int x)
    {
        return a[x];
    }

    inline matrix operator * (const matrix M) const
    {
        matrix res;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    return 0;
}
