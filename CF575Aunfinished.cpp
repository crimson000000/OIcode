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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e5 + 10;

ll n, m, p, k;
ll a[N];
pair<ll, ll> ch[N];
struct mat
{
    ll a[5][5];
    int n, m;

    ll* operator [] (int x) 
    {
        return a[x];
    }

    void init()
    {
        memset(a, 0, sizeof a);
    }

    void I(int k)
    {
        n = k, m = k;
        for(int i = 1; i <= k; i ++ ) a[i][i] = 1;
    }

    mat operator * (const mat &M) const
    {
        mat tmp;
        tmp.n = n, tmp.m = M.m;
        for(int i = 1; i <= n; i ++ )
            for(int k = 1; k <= M.m; k ++ )
                for(int j = 1; j <= m; j ++ )
                    tmp[i][j] = (tmp[i][j] + a[i][k] * M.a[k][j] % p) % p;
        return tmp;
    }
}b[N];

struct segmenttree
{
    struct segment
    {
        int l, r;
        mat v;
    }t[N << 2];

    inline void pushup(int p)
    {
        t[p].v = t[p << 1].v * t[p << 1 | 1].v;
    }

    void build(int p, int l, int r)
    {
        t[p].l = l, t[p].r = r;
        if(l == r) t[p].v = b[l];
        int mid = l + r >> 1;
        build(p << 1, l, mid);
        build(p << 1 | 1, mid + 1, r);
        pushup(p);
    }

    void change(int p, int pos, int x, ll v)
    {
        if(t[p].l == t[p].r)
        {
            t[p].v[x][2] = v;
            return;
        }
        int mid = t[p].l + t[p].r >> 1;
        if(pos <= mid) change(p << 1, pos, x, v);
        else change(p << 1 | 1, pos, x, v);
        pushup(p);
    }

    mat query(int p, int l, int r)
    {
        if(t[p].l >= l && t[p].r <= r)
            return t[p].v;
        int mid = t[p].l + t[p].r >> 1;
        mat res;
        res.I(2);
        if(l <= mid) res = res * query(p << 1, l, r);
        if(r > mid) res = res * query(p << 1 | 1, l, r);
        return res;
    }
}t;

mat qmi(mat a, ll k)
{
    mat res;
    res.init();
    res.I(2);
    while(k)
    {
        if(k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

int cur = 1;
mat ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    k = read(), p = read();
    n = read();
    for(int i = 0; i < n; i ++ )
    {
        a[i] = read();
    }

    m = read();

    for(int i = 1; i <= m; i ++ )
    {
        ch[i].first = read(), ch[i].second = read();
    }

    sort(ch + 1, ch + 1 + m);
    for(int i = 1; i <= n; i ++ )
    {
        b[i][1][1] = 0, b[i][1][2] = a[i - 1];
        b[i][2][1] = 1, b[i][2][2] = a[i % n];
    }
    
    t.build(1, 1, n);
    ans.n = 1, ans.m = 2, ans[1][1] = 0, ans[1][2] = 1;

    if(k < n)
    {
        ans = ans * qmi(t.query(1, 1, k));
        cout << ans[1][1] << endl;
    }
    

    return 0;
}
