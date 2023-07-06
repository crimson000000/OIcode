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

ll d[70];
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
ll n, m, cnt;

bool insert(ll x)
{
    for(int i = 63; i >= 0; i -- )
    {
        if(x >> i & 1)
        {
            if(!d[i])
            {
                cnt ++;
                d[i] = x;
                return true;
            }
            else x ^= d[i];
        }
    }
    return false;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        ll x = 0;
        char s[70];
        scanf("%s", s);
        int len = strlen(s);
        for(int i = 0; i < len; i ++ )
            if(s[i] == 'O')
                x |= 1ll << n - i;
        insert(x);
    }
    
    cout << qmi(2, cnt, 2008) << endl;

    return 0;
}
