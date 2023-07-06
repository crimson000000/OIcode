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

const int N = 1e6 + 10;
int q[20][2];
int primes[N], cnt, maxx;
int ans[N], tot;
int phi[N];
int p[N];
bool st[N], f[N], vis[N];

void init(int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
            phi[i] = i - 1;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) 
            {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            else phi[i * primes[j]] = phi[i] * (primes[j] - 1);
        }
    }
}

ll qmi(ll a, ll k, ll p)
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

    int T = read();
    for(int i = 1; i <= T; i ++ ) 
    {
        q[i][0] = read(), q[i][1] = read();
        maxx = max(maxx, q[i][0]);
    }

    init(maxx);
    f[2] = f[4] = true;
    for(int i = 2; i <= cnt; i ++ )
    {
        int p = primes[i];
        for(int j = 1; (ll)j * p <= maxx; j *= p) f[j * p] = true;
        for(int j = 2; (ll)j * p <= maxx; j *= p) f[j * p] = true;
    }

    for(int t = 1; t <= T; t ++ )
    {
        int mod = q[t][0], d = q[t][1];
        if(f[mod] == false)
        {
            printf("0\n\n");
            continue;
        }

        int x = phi[mod], sum = 0, g = 0, tot = 0;
        for(int i = 1; i <= cnt && primes[i] <= x / primes[i]; i ++ )
        {
            if(x % primes[i] == 0)
            {
                while(x % primes[i] == 0) x /= primes[i];
                p[++ sum] = primes[i];
                for(int j = 1; j <= phi[mod] / primes[i]; j ++ )
                    vis[j * primes[i]] = true;
            }
        }
        if(x > 1) 
        {
            p[++ sum] = x;
            for(int j = 1; j <= phi[mod] / x; j ++ ) vis[j * x] = true;
        }
        for(int i = 1; i < mod; i ++ )
        {
            while(qmi(i, phi[mod], mod) != 1) i ++;
            bool flag = true;
            for(int j = 1; j <= sum && flag == true; j ++ )
                if(qmi(i, phi[mod] / p[j], mod) == 1)
                    flag = false;
            if(flag)
            {
                g = i;
                break;
            }
        }
        for(int i = 1, x = g; i <= phi[mod]; i ++, x = (ll)x * g % mod)
        {
            if(!vis[i]) ans[++ tot] = x;
            else vis[i] = false;
        }
        sort(ans + 1, ans + tot + 1);
        printf("%d\n", tot);
        for(int i = 1; i <= tot / d; i ++ ) printf("%d ", ans[i * d]);
        puts("");
    }
    
    
    return 0;
}
