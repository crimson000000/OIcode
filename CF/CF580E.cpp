#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using i128 = __int128;
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

const int N = 1e5 + 10;
const ll mod = 9223372036854775783, P = 131;
char s[N];
ll ppow[N];
ll chash[N][10];
int n, m, k;

inline void init()
{
    for(int i = 0; i <= 9; i ++ )
    {
        char c = i + '0';
        chash[0][i] = 0;
        for(int j = 1; j <= n; j ++ )
            chash[j][i] = ((i128)chash[j - 1][i] * P + c) % mod;
    }

    ppow[0] = 1;
    for(int i = 1; i <= n; i ++ ) ppow[i] = (i128)ppow[i - 1] * P % mod;
}

struct node
{
    int l, r;
    ll hash;
    int cov;
}t[N << 2];

inline void pushup(int p)
{
    t[p].hash = ((i128)t[p << 1].hash * ppow[ (t[p << 1 | 1].r - t[p << 1 | 1].l + 1) ] % mod + 
                t[p << 1 | 1].hash) % mod;
}

inline void pushdown(int p)
{
    if(t[p].cov != -1)
    {
        t[p << 1].hash = chash[t[p << 1].r - t[p << 1].l + 1][t[p].cov];
        t[p << 1 | 1].hash = chash[t[p << 1 | 1].r - t[p << 1 | 1].l + 1][t[p].cov];
        t[p << 1].cov = t[p].cov;
        t[p << 1 | 1].cov = t[p].cov;
        t[p].cov = -1;
    }
}

inline void build(int p, int l, int r)
{
    t[p].l = l, t[p].r = r;
    t[p].cov = -1;
    if(l == r)
    {
        t[p].hash = s[l];
        return;
    }
    int mid = l + r >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
    pushup(p);
}

inline void cover(int p, int l, int r, int v)
{
    if(t[p].l >= l && t[p].r <= r)
    {
        t[p].cov = v;
        t[p].hash = chash[t[p].r - t[p].l + 1][v];
        return;
    }
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(l <= mid) cover(p << 1, l, r, v);
    if(r > mid) cover(p << 1 | 1, l, r, v);
    pushup(p);
}

inline ll query(int p, int l, int r)
{
    if(l > r) return 0;
    if(t[p].l >= l && t[p].r <= r) return t[p].hash;
    pushdown(p);
    int mid = t[p].l + t[p].r >> 1;
    if(r <= mid) return query(p << 1, l, r);
    if(l > mid) return query(p << 1 | 1, l, r);
    ll lhash = query(p << 1, l, r), rhash = query(p << 1 | 1, l, r);
    ll res = ((i128)lhash * ppow[min(t[p << 1 | 1].r, r) - t[p << 1 | 1].l + 1] % mod + 
                rhash) % mod;
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), k = read();

    scanf("%s", s + 1);    
    init();

    build(1, 1, n);

    for(int T = 1; T <= m + k; T ++ )
    {
        int op = read(), l = read(), r = read(), c = read();
        if(op == 1)
        {
            cover(1, l, r, c);
        }
        else
        {
            c = r - l + 1 - c;
            ll ahash = query(1, l, l + c - 1);
            ll bhash = query(1, r - c + 1, r);
            // cout << l << ' ' << l + c - 1 << endl;
            // cout << r - c + 1 << ' ' << r << endl;
            // cout << ahash << ' ' << bhash << endl;
            if(ahash == bhash) puts("YES");
            else puts("NO");
        }
    }

    return 0;
}