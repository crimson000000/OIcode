#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

const int N = 1e6 + 10;
int n, m;
int p[N];
int bef[N], rec[N];
ll tot;

struct ta
{
    ll c[N];
    #define lowbit(x) x & -x
    void add(int x, ll v)
    {
        for(; x <= n; x += lowbit(x)) c[x] += v;
    }

    ll query(int x)
    {
        ll res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        p[i] = read();
        bef[i] = i - bit.query(p[i]) - 1;
        rec[bef[i]] ++;
        tot += bef[i];
        bit.add(p[i], 1);
    }

    memset(bit.c, 0, sizeof bit.c);

    bit.add(1, tot);
    tot = 0;
    for(int i = 0; i < n; i ++ )
    {
        tot += rec[i];
        bit.add(i + 2, -(n - tot));
    }

    while(m -- )
    {
        int op = read(), x = read();
        x = min(x, n - 1);
        if(op == 1)
        {
            if(p[x] < p[x + 1])
            {
                swap(p[x], p[x + 1]);
                swap(bef[x], bef[x + 1]);
                bit.add(1, 1);
                bit.add(bef[x + 1] + 2, -1);
                bef[x + 1] ++;
            }
            else
            {
                swap(p[x], p[x + 1]);
                swap(bef[x], bef[x + 1]);
                bit.add(1, -1);
                bef[x] --;
                bit.add(bef[x] + 2, 1);
            }
        }
        else printf("%lld\n", bit.query(x + 1));
    }

    return 0;
}