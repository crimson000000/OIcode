#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

const int N = 2e6 + 10;
ll a[N];
int n;
int p, cnt, op, d;

inline void first()
{
    puts("First");
    exit(0);
}

inline void sec()
{
    puts("Second");
    exit(0);
}

inline ll gcd(ll a, ll b)
{
    return b ? gcd(b, a % b) : a;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    while(1)
    {
        cnt = d = 0;
        bool flag = false;
        for(int i = 1; i <= n; i ++ )
        {
            if((a[i] & 1) && a[i] > 1) cnt ++, p = i;
            else if(!(a[i] & 1)) d ++;
            if(a[i] == 1) flag = true;
        }
        if(flag)
        {
            if(d & 1)
            {
                if(!op) first();
                else sec();
            }
            else
            {
                if(op) first();
                else sec();
            }
        }
        if(d & 1)
        {
            if(!op) first();
            else sec();
        }
        if(!(d & 1) && cnt > 1)
        {
            if(op) first();
            else sec();
        }
        a[p] --;
        ll g = 0;
        for(int i = 1; i <= n; i ++ ) g = gcd(g, a[i]);
        for(int i = 1; i <= n; i ++ ) a[i] /= g;
        op ^= 1;
    }

    return 0;
}
