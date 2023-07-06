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

const int N = 2e6 + 10;
int n, p;
int primes[N], v[N], pcnt;
int cnt[N];

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

void init(int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!v[i])
        {
            primes[pcnt ++ ] = i;
            v[i] = i;
        }
        for(int j = 0; primes[j] <= n / i; j ++ )
        {
            v[i * primes[j]] = primes[j];
            if(i % primes[j] == 0) break;
        }
    }
}

int main() 
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n >> p;
    
    init(n << 1);

    for(int i = 1; i <= n; i ++ ) cnt[i] --;
    for(int i = n + 2; i <= 2 * n; i ++ )
        cnt[i] ++;
    
    for(int i = 2 * n; i > 1; i -- )
        if(v[i] != i)
        {
            cnt[v[i]] += cnt[i];
            cnt[i / v[i]] += cnt[i];
        }

    int ans = 1;
    for(int i = 2; i <= 2 * n; i ++ )
        if(v[i] == i)
        {
            ans = (ll)ans * qmi(i, cnt[i], p) % p;
        }

    cout << ans << endl;

    return 0;
}
