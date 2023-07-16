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

const int N = 1e6 + 10, mod = 1e9;
int p[N], g[N];
int a[N], b[N], XOR[N];
int n, m, k;

inline int find(int x)
{
    if(p[x] == x) return x;
    int rt = find(p[x]);
    g[x] ^= g[p[x]];
    return p[x] = rt;
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

inline ll calc(int opt)
{
    for(int i = 1; i <= n + m; i ++ )
    {
        p[i] = i;
        g[i] = 0;
    }

    p[n + 1] = p[1];

    if(opt)
    {
        for(int i = 1; i <= k; i ++ )
            if(a[i] != 1 && b[i] != 1)
                XOR[i] ^= 1;
    }

    for(int i = 1; i <= k; i ++ )
    {
        int x = a[i], y = b[i], z = XOR[i];
        if(x != 1 || y != 1)
        {
            int fx = find(x), fy = find(y + n);
            int ty = g[x] ^ g[y + n] ^ z;
            if(fx != fy)
            {
                p[fy] = fx;
                g[fy] = ty;
            }
            else if(ty) return 0;
        }
    }

    int cnt = 0;
    for(int i = 1; i <= n + m; i ++ )
        if(find(i) == i)
            cnt ++;
    
    return qmi(2, cnt - 1, mod);
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();
    
    int flag = -1;
    for(int i = 1; i <= k; i ++ )
    {
        a[i] = read(), b[i] = read(), XOR[i] = read();
        if((!(a[i] & 1)) && (!(b[i] & 1)))
            XOR[i] ^= 1;
        if(a[i] == 1 && b[i] == 1)
            flag = XOR[i];
    }

    if(flag != -1) printf("%lld\n", calc(flag));
    else printf("%lld\n", (calc(1) + calc(0)) % mod);

    return 0;
}
