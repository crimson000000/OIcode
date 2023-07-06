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

const int N = 1e7 + 10;
int primes[N], cnt;
bool st[N];
ll phi[N];

void init(int n)
{
    phi[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[cnt ++ ] = i;
            phi[i] = i - 1;
        }
        for(int j = 0; primes[j] <= n / i; j ++ )
        {
            int t = primes[j] * i;
            st[t] = true;
            if(i % primes[j] != 0) phi[t] = phi[i] * (primes[j] - 1);
            else
            {
                phi[t] = phi[i] * primes[j];
                break;
            }
        }
    }
}

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

ll work(ll p)
{
    if(p == 1) return 0;
    return qmi(2, work(phi[p]) + phi[p], p);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T;
    cin >> T;

    init(N - 1);
    // for(int i = 1; i <= 10; i ++ ) cout << phi[i] << ' ';

    while(T -- )
    {
        ll p;
        cin >> p;
        cout << work(p) << endl;
    }
    
    return 0;
}
