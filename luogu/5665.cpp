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

inline void write(__int128 x)
{
    if(x < 0)
        putchar('-'), x = -x;
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
    return;
}

const int N = 4e7 + 10, M = 1e5 + 10;
const ll ANDMOD = (1 << 30) - 1;
int lst[N];
ll s[N];

int n, type;

namespace ge
{
    int x, y, z, m;
    int p[M], l[M], r[M];
    inline void generate(int type)
    {
        if(type == 0)
        {
            for(int i = 1; i <= n; i ++ )
            {
                s[i] = s[i - 1] + read();
            }
        }
        else
        {
            x = read(), y = read(), z = read();
            s[1] = read(), s[2] = read(), m = read();
            for(int i = 1; i <= m; i ++ )
            {
                p[i] = read();
                l[i] = read();
                r[i] = read();
            }

            for(int i = 3; i <= n; i ++ ) 
                s[i] = (((s[i - 1] * x) & ANDMOD) + ((y * s[i - 2]) & ANDMOD) + z) & ANDMOD;
            
            for(int j = 1; j <= m; j ++ )
            {
                for(int i = p[j - 1] + 1; i <= p[j]; i ++ )
                {
                    s[i] = (s[i] % (r[j] - l[j] + 1)) + l[j] + s[i - 1];
                }
            }
        }
    }
}

int q[N];
int hh = 1, tt = 1;

inline ll A(int x)
{
    return 2 * s[x] - s[lst[x]];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), type = read();
    ge::generate(type);

    for(int i = 1; i <= n; i ++ )
    {
        int last = 0;
        while(hh != tt && s[i] >= A(q[hh])) 
        {
            last = q[hh];
            hh ++;
        }
        lst[i] = last;
        q[-- hh] = last;

        ll Ai = A(i);
        while(hh != tt && Ai <= A(q[tt - 1])) tt --;
        q[tt ++ ] = i;
    }

    __int128 ans = 0;
    for(int i = n; i; i = lst[i])
    {
        ans += (__int128)(s[i] - s[lst[i]]) * (s[i] - s[lst[i]]);
    }

    write(ans);

    return 0;
}