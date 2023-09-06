#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

const int N = 1e6 + 10;
int fa[N][20];
int n, m;

inline int find(int x, int k)
{
    if(fa[x][k] != x) fa[x][k] = find(fa[x][k], k);
    return fa[x][k];
}

inline void merge(int x, int y, int k)
{
    x = find(x, k), y = find(y, k);
    if(x != y) fa[x][k] = y;
}

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

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 19; i >= 0; i -- )
        for(int j = 1; j <= n; j ++ )
            fa[j][i] = j;
    
    while(m -- )
    {
        int l1 = read(), r1 = read(), l2 = read(), r2 = read();
        for(int k = 19; k >= 0; k -- )
            if(l1 + (1 << k) - 1 <= r1)
            {
                merge(l1, l2, k);
                l1 += 1 << k;
                l2 += 1 << k;
            }
    }

    for(int k = 19; k; k -- )
        for(int i = 1; i + (1 << k) - 1 <= n; i ++ )
        {
            int p = find(i, k);
            merge(i, p, k - 1);
            merge(i + (1 << (k - 1)), p + (1 << (k - 1)), k - 1);
        }

    int cnt = 0;
    for(int i = 1; i <= n; i ++ ) 
        if(find(i, 0) == i)
            cnt ++;
    
    printf("%lld\n", 9 * qmi(10, cnt - 1, 1000000007) % 1000000007);

    return 0;
} 