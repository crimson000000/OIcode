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
int a[N];

struct ta
{
    int c[N];
    #define lowbit(x) x & -x
    void add(int x, int v)
    {
        for(; x <= 1e5; x += lowbit(x)) c[x] += v;
    }

    int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
}bit;

struct query
{
    int l, r, a, b, id;
}q[N], q1[N];
int pos[N];
int ans1[N], ans2[N];
int L, R;

int cnt[N];
void add(int pos)
{
    if(!cnt[a[pos]]) bit.add(a[pos], 1);
    cnt[a[pos]] ++;
}

void sub(int pos)
{
    cnt[a[pos]] --;
    if(!cnt[a[pos]]) bit.add(a[pos], -1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    int _ = sqrt(n);
    for(int i = 1; i <= n; i ++ ) pos[i] = (i - 1) / _ + 1;
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= m; i ++ )
    {
        int l = read(), r = read(), a = read(), b = read();
        q[i] = {1, r, a, b, i};
        q[i + m] = {-1, l - 1, a, b, i};
        q1[i] = {l, r, a, b, i};
    }

    sort(q + 1, q + 2 * m + 1, [](query x, query y){
        return x.r < y.r;
    });

    R = 0;
    for(int i = 1; i <= 2 * m; i ++ )
    {
        while(R < q[i].r)
        {
            R ++;
            bit.add(a[R], 1);
        }
        ans1[q[i].id] += q[i].l * (bit.query(q[i].b) - bit.query(q[i].a - 1));
    }

    memset(bit.c, 0, sizeof bit.c);
    sort(q1 + 1, q1 + m + 1, [](query x, query y){
        if(pos[x.l] != pos[y.l]) return pos[x.l] < pos[y.l];
        return pos[x.r] < pos[y.r];
    });

    L = 1, R = 0;
    for(int i = 1; i <= m; i ++ )
    {
        while(R < q1[i].r) add(++ R);
        while(L > q1[i].l) add(-- L);
        while(R > q1[i].r) sub(R -- );
        while(L < q1[i].l) sub(L ++ );
        ans2[q1[i].id] = bit.query(q1[i].b) - bit.query(q1[i].a - 1);
    }

    for(int i = 1; i <= m; i ++ )
        printf("%d %d\n", ans1[i], ans2[i]);

    return 0;
}