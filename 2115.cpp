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

const int N = 1e7 + 100, M = 1e6 + 10;
int p, T;
int n, m;
int fact[N];
int inv[N], up[M], down[M];
int pos[N];
int primes[M], cnt;
bool st[N];

void init(int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i]) 
        {
            primes[++ cnt] = i;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
    
    inv[1] = 1;
    for(int i = 2; i <= n; i ++ )
        inv[i] = (p - p / i) * (ll)inv[p % i] % p;

    up[0] = 1;
    for(int i = 1; i <= cnt; i ++ ) up[i] = (ll)up[i - 1] * (primes[i] - 1) % p;

    down[0] = 1;
    for(int i = 1; i <= cnt; i ++ )
        if(primes[i] != p)
            down[i] = (ll)down[i - 1] * inv[primes[i] % p] % p;
        else down[i] = down[i - 1];

    fact[0] = 1;
    for(int i = 1; i <= n; i ++ ) 
        if(i != p)
            fact[i] = (ll)fact[i - 1] * i % p;
        else fact[i] = fact[i - 1];

    for(int i = 2; i <= n; i ++ )
        if(st[i]) pos[i] = pos[i - 1];
        else pos[i] = pos[i - 1] + 1;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> T >> p;

    init(N - 99);
    // cout << phi[4] << endl;

    while(T -- )
    {
        cin >> n >> m;
        if(n >= p && m < p) puts("0");
        else cout << (ll)fact[n] * up[pos[m]] % p * down[pos[m]] % p << endl;
    }
    
    return 0;
}
