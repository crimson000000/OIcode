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

const int N = 1e5 + 10;
ll a[N], s[N];
int n, m, q;

inline void write2(ll x)
{
    for(int i = 1; i <= n + 1; i ++ ) 
        if(x >> i & 1) putchar('1');
        else putchar('0');
    puts("");
}

inline void build()
{
    for(int i = 1; i <= m; i ++ )
    {
        for(int j = 0; j < n; j ++ )
            if(s[i] >> j & 1)
                a[i] |= (1ll << (j + 1));
        a[i] |= (1ll << (n + 1));
    }
}

bitset<N> f;
ll d[N];
int line_cnt;
inline bool gauss()
{
    // for(int i = 1; i <= m; i ++ )
    //     write2(a[i]);
    // puts("");

    int cnt = 1;
    for(int i = 1; i <= n; i ++ )
    {
        int pos = 0;
        for(int j = cnt; j <= m; j ++ )
            if(a[j] >> i & 1)
            {
                pos = j;
                break;
            }
        if(pos == 0) continue;
        cnt ++;
        swap(a[i], a[pos]);
        for(int j = 1; j <= m; j ++ )
        {
            if(j == i) continue;
            if(!(a[j] >> i & 1)) continue;
            a[j] ^= a[i];
        }
    }

    for(int i = cnt + 1; i <= m; i ++ )
    {
        for(int j = 1; j <= n; j ++ )
            if(a[i] >> j & 1)
                a[i] ^= a[j];
    }

    for(int i = 1; i <= m; i ++ )
        write2(a[i]);

    for(int i = 1; i <= m; i ++ )
    {
        bool flag = false;
        for(int j = 1; j <= n; j ++ )
            if(a[i] >> j & 1)
                flag = true;
        if(!flag && (a[i] >> (n + 1) & 1)) return false;
        if(flag) line_cnt ++;
    } 

    for(int i = 1; i <= m; i ++ )
        for(int j = 1; j <= n; j ++ )
            if(a[i] >> j & 1)
            {
                d[j] = a[i];
                f[j] = false;
                break;
            }

    // cout << d[2] << endl;

    return true;
}

inline bool line()
{
    for(int j = 1; j <= m; j ++ )
    {
        ll x = a[j];
        for(int i = n; i > 0; i -- )
        {
            if(!(x >> i & 1)) continue;
            if(!d[i])
            {
                d[i] = x;
                for(int k = n; k > i; k -- ) 
                    if(d[k] >> i & 1)
                        d[k] ^= d[i];

                for(int k = 1; k < i; k ++ ) 
                    if(d[i] >> k & 1)
                        d[i] ^= d[k];

                line_cnt ++;
                f[i] = false;
                break;
            }
            x ^= d[i];
        }

        bool flag = false;
        for(int i = 1; i <= n; i ++ )   
            if(x >> i & 1)
                flag = true;
        
        if(!flag && (x >> (n + 1) & 1)) return false;
    }
    return true;
}

inline void see()
{
    for(int i = 1; i <= n; i ++ )
        write2(d[i]);
}

inline void nosol()
{
    while(q -- ) 
    {
        ll x = read();
        puts("0");
    }
}

inline void getans(ll x)
{
    a[m + 1] = 0;
    for(int i = 1; i <= n; i ++ )
        if(x >> (i - 1) & 1)
            a[m + 1] |= (1ll << i);
    a[m + 1] |= (1ll << (n + 1));

    // write2(a[m + 1]);

    for(int i = 1; i <= n; i ++ )
        if(a[m + 1] >> i & 1)
            a[m + 1] ^= d[i];

    // write2(a[m + 1]);

    int cnt = 0;
    for(int i = 1; i <= n; i ++ )
        if((a[m + 1] >> i & 1) && f[i])
            cnt = 1;

    bool flag = false;
    for(int i = 1; i <= n; i ++ )
        if(a[m + 1] >> i & 1)
            flag = true;
    
    if(!flag && (a[m + 1] >> (n + 1) & 1)) puts("0"); 
    else printf("%lld\n", 1ll << (n - (line_cnt + cnt)));
}

inline void solve()
{
    line_cnt = 0;
    f.set();
    memset(a, 0, sizeof a);
    memset(d, 0, sizeof d);
    n = read(), m = read(), q = read();
    for(int i = 1; i <= m; i ++ ) s[i] = read();
    
    build();

    if(!line()) nosol();
    else 
    {
        // see();
        // cout << line_cnt << endl;
        while(q -- )
        {
            ll x = read();
            getans(x);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
} 