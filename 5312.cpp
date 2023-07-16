#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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
int len;
ll a[N];
int sum[N][32];
ll XOR;
bitset<N> tag;

inline void gettag()
{
    for(int i = 30; i >= 0; i -- ) tag[i] = (XOR >> i & 1);
}

int tr[N * 10][2], siz[N * 10], cnt[N * 5][32], idx = 1;
inline void insert(int x)
{
    int p = 1;
    for(int i = 30; i >= 0; i -- )
    {
        siz[p] ++;
        for(int j = 30; j >= 0; j -- ) cnt[p][j] += (x >> j & 1);
        int v = x >> i & 1;
        if(!tr[p][v]) tr[p][v] = ++ idx;
        p = tr[p][v];
    }
    siz[p] ++;
    for(int j = 30; j >= 0; j -- ) cnt[p][j] += (x >> j & 1);
}

inline ll query(int x)
{
    if(!x) return 0;
    int p = 1;
    ll res = 0, ans = 0;
    for(int i = 30; i >= 0; i -- )
    {
        if(x <= siz[tr[p][tag[i]]]) 
        {
            p = tr[p][tag[i]];
            res |= (1ll * tag[i]) << i;
        }
        else
        {
            x -= siz[tr[p][tag[i]]];
            for(int j = 0; j <= 30; j ++ )
            {
                if(XOR >> j & 1)
                {
                    ans += 1ll * (siz[tr[p][tag[i]]] - cnt[tr[p][tag[i]]][j]) << j;
                }
                else
                {
                    ans += 1ll * cnt[tr[p][tag[i]]][j] << j;
                }
            }
            p = tr[p][tag[i] ^ 1];
            res |= (1ll * (tag[i] ^ 1)) << i;
        }
    }
    return ans + (res ^ XOR) * x;
}

inline ll query(int l, int r)
{
    if(r <= len) return query(r) - query(l - 1);
    int ln = r - l + 1;
    if(l > len)
    {
        ll ans = 0;
        for(int i = 30; i >= 0; i -- )
        {
            if(XOR >> i & 1) 
                ans += (ln - sum[r][i] + sum[l - 1][i]) * (1ll << i);
            else ans += (sum[r][i] - sum[l - 1][i]) * (1ll << i);
        }
        return ans;
    }
    ll ans = query(len) - query(l - 1);
    ln = r - len;
    for(int i = 30; i >= 0; i -- )
    {
        if(XOR >> i & 1) 
            ans += (ln - sum[r][i]) * (1ll << i);
        else ans += (sum[r][i]) * (1ll << i);
    }
    return ans;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    len = 0;
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        for(int j = 0; j <= 30; j ++ )
            sum[i][j] = sum[i - 1][j] + (a[i] >> j & 1);
    }

    m = read();

    while(m -- )
    {
        int op = read();
        if(op == 1)
        {
            int x = read();
            a[++ n] = x ^ XOR;
            for(int i = 0; i <= 30; i ++ )
                sum[n][i] = sum[n - 1][i] + (a[n] >> i & 1);
        }
        else if(op == 2)
        {
            int l = read(), r = read();
            printf("%lld\n", query(l, r));
        }
        else if(op == 3)
        {
            int x = read();
            XOR ^= x;
        }
        else
        {
            for(int i = len + 1; i <= n; i ++ ) insert(a[i]);
            gettag();
            len = n;
            for(int i = 0; i <= 30; i ++ ) sum[n][i] = 0;
        }
    }

    return 0;
}
