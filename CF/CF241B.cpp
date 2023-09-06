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

const int N = 2e5 + 10, mod = 1e9 + 7;
ll a[N];
ll sum[33][2][N];
ll n, m;

inline ll qmi(ll a, ll k, ll p)
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

inline ll add(ll a, ll b)
{
    return ((a + b) % mod + mod) % mod;
}

struct trie
{
    struct node
    {
        int ch[2];
        int siz, l, r;
    }t[N * 10];
    int tmp[N];
    int idx, root;

    inline void insert(ll x, int id)
    {
        if(!root) 
        {
            root = ++ idx;
            t[root].l = 1, t[root].r = n;
        }
        int p = root;
        t[p].siz ++;
        for(int i = 31; i >= 0; i -- )
        {
            int v = x >> i & 1;
            int &now = t[p].ch[v];
            if(!now) now = ++ idx, t[now].l = id;
            p = now;
            t[p].r = id;
            t[p].siz ++;
        }
    }

    inline ll getval(ll &k)
    {
        ll res = 0;
        for(int i = 1; i <= n; i ++ ) tmp[i] = root;
        for(int d = 31; d >= 0; d -- )
        {
            int cnt = 0, x;
            for(int i = 1; i <= n; i ++ ) cnt += t[t[tmp[i]].ch[(a[i] >> d & 1) ^ 1]].siz;
            if(cnt >= k) res |= (1 << d), x = 1;
            else x = 0, k -= cnt;
            for(int i = 1; i <= n; i ++ )
                tmp[i] = t[tmp[i]].ch[(a[i] >> d & 1) ^ x];
        }
        return res;
    }

    inline ll ask(int l, int r, ll val)
    {
        if(!l || !r) return 0;
        ll res = 0;
        for(int d = 31; d >= 0; d -- )
            res = add(res, ((ll)sum[d][(val >> d & 1) ^ 1][r] - sum[d][(val >> d & 1) ^ 1][l - 1]) % mod * (1ll << d) % mod);
        return res;
    }

    inline ll getsum(ll k)
    {
        ll val = getval(k);
        ll res = val * k % mod;
        for(int i = 1; i <= n; i ++ ) tmp[i] = root;
        for(int d = 31; d >= 0; d -- )
        {
            int x = val >> d & 1;
            if(!x)
            {
                for(int i = 1; i <= n; i ++ )
                    res = add(res, ask(t[t[tmp[i]].ch[(a[i] >> d & 1) ^ 1]].l, t[t[tmp[i]].ch[(a[i] >> d & 1) ^ 1]].r, a[i]));
            }
            for(int i = 1; i <= n; i ++ )
                tmp[i] = t[tmp[i]].ch[(a[i] >> d & 1) ^ x];
        }
        return res;
    }
}t;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read() * 2;
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    sort(a + 1, a + 1 + n);

    for(int i = 1; i <= n; i ++ ) t.insert(a[i], i);
    for(int i = 1; i <= n; i ++ )
    {
        for(int d = 31; d >= 0; d -- )
        {
            sum[d][0][i] = sum[d][0][i - 1];
            sum[d][1][i] = sum[d][1][i - 1];
            sum[d][a[i] >> d & 1][i] ++;
        }
    }

    cout << t.getsum(m) * qmi(2, mod - 2, mod) % mod << endl;

    return 0;
}