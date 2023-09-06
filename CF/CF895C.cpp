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

const int N = 1e5 + 10, mod = 1e9 + 7;
int a[N];
bool st[N];
ll vis[N], cc;
int n;

ll d[N], cnt;
void insert(ll x)
{
    for(int i = 30; i >= 0; i -- )
    {
        if(x >> i & 1)
        {
            if(!d[i]) 
            {
                d[i] = x;
                cnt ++;
                return;
            }
            x ^= d[i];
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

    for(int i = 2; i <= 80; i ++ )
    {
        if(!st[i])
        {
            vis[i] = 1 << cc;
            cc ++;
        }
        for(int j = i * i; j <= 80; j += i)
            st[j] = true;
    }

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        int p = a[i];
        ll s = 0;
        for(int j = 2; j <= p / j; j ++ )
        {
            while(p % j == 0) s ^= vis[j], p /= j;
        }
        if(p > 1) s ^= vis[p];
        insert(s);
    }

    cout << qmi(2, n - cnt, mod) - 1 << endl;
    
    return 0;
}
