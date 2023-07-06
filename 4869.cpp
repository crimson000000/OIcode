#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

template <typename T>
inline T read()
{
    T x = 0, f = 1;
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

const int N = 1e5 + 10, mod = 10086;
ll d[N], a[N];
int stk[N], tt;
ll n, m, cnt;

bool insert(ll x)
{
    for(int i = 32; i >= 0; i -- )
    {
        if(x >> i & 1)
        {
            if(!d[i])
            {
                d[i] = x;
                return true;
            }
            x ^= d[i];
        }
    }
    return false;
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

ll ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read<ll>();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read<ll>();
        if(insert(a[i]))
        {
            cnt ++;
        }
    }

    m = read<ll>();

    for(int i = 0; i <= 30; i ++ )
        if(d[i])
            stk[++ tt] = i;
    
    for(int i = 1; i <= tt; i ++ )
        if(m >> stk[i] & 1)
            ans += 1 << i - 1;
    
    cout << ans * qmi(2, n - tt, mod) % mod + 1 << endl;
     
    return 0;
}
