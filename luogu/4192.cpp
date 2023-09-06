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

const int N = 1e6 + 10, M = 1010;
ll a[N], sum[N];
int pos[N];
int B, T;
int n, m;

struct point
{
    ll x, y;
};

double slope(point a, point b)
{
    return 1.0 * (a.y - b.y) / (a.x - b.x);
}

struct Block
{
    int L, R;
    ll d, add;
    point a[M];
    int stk[M], tt;

    void build()
    {
        for(int i = L; i <= R; i ++ )
            sum[i] += add + (i - L + 1) * d;

        add = d = 0;
        for(int i = 1; i <= R - L + 1; i ++ )
            a[i] = {i, sum[i + L - 1]};

        tt = 0;
        stk[++ tt] = 1;
        for(int i = 2; i <= R - L + 1; i ++ )
        {
            while(tt > 1 && slope(a[stk[tt]], a[stk[tt - 1]]) <= slope(a[stk[tt]], a[i]))
                tt --;
            stk[++ tt] = i;
        }
    }

    ll get(ll pos)
    {
        return sum[pos] + add + (pos - L + 1) * d;
    }

    void Add(ll st, ll k)
    {
        add += st;
        d += k;
    }

    ll query()
    {
        int l = 1, r = tt;
        while(l < r)
        {
            int mid = l + r >> 1;
            if(slope(a[stk[mid]], a[stk[mid + 1]]) < -d) r = mid;
            else l = mid + 1;
        }
        return a[stk[l]].y + add + a[stk[l]].x * d;
    }
}bl[M];

void change(int l, int r, ll k)
{
    ll st = 0;
    if(pos[l] == pos[r])
    {
        for(int i = l; i <= r; i ++ )
        {
            st += k;
            sum[i] += st;
        }
        bl[pos[l]].build();
        return;
    }
    for(int i = l; i <= bl[pos[l]].R; i ++ )
    {
        st += k;
        sum[i] += st;
    }
    bl[pos[l]].build();
    for(int i = pos[l] + 1; i <= pos[r] - 1; i ++ ) 
    {
        bl[i].Add(st, k);
        st += (bl[i].R - bl[i].L + 1) * k;
    }
    for(int i = bl[pos[r]].L; i <= r; i ++ )
    {
        st += k;
        sum[i] += st;
    }
    bl[pos[r]].build();
}

void add(int l, int r, ll k)
{   
    if(pos[l] == pos[r])
    {
        for(int i = l; i <= r; i ++ )
            sum[i] += k;
        bl[pos[l]].build();
        return;
    }
    for(int i = l; i <= bl[pos[l]].R; i ++ ) sum[i] += k;
    bl[pos[l]].build();
    for(int i = pos[l] + 1; i <= pos[r] - 1; i ++ ) bl[i].Add(k, 0);
    for(int i = bl[pos[r]].L; i <= r; i ++ ) sum[i] += k;
    if(r == bl[pos[r]].R) bl[pos[r]].build();
}

ll query(int l, int r)
{
    if(pos[l] == pos[r])
    {
        ll res = -0x3f3f3f3f3f3f3f3f;
        for(int i = l; i <= r; i ++ ) res = max(res, bl[pos[l]].get(i));
        return res;
    }
    ll res = -0x3f3f3f3f3f3f3f3f;
    for(int i = l; i <= bl[pos[l]].R; i ++ ) res = max(res, bl[pos[l]].get(i));
    for(int i = pos[l] + 1; i <= pos[r] - 1; i ++ ) res = max(res, bl[i].query());
    for(int i = bl[pos[r]].L; i <= r; i ++ ) res = max(res, bl[pos[r]].get(i));
    return res;
}

void print()
{
    for(int i = 1; i <= T; i ++ ) bl[i].build();
    for(int i = 1; i <= n; i ++ ) cout << sum[i] << ' ';
    puts("");
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    B = sqrt(n), T = n / B;
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        sum[i] = sum[i - 1] + a[i];
    }

    for(int i = 1; i <= T; i ++ )   
    {
        bl[i].L = (i - 1) * B + 1;
        bl[i].R = i * B;
    }

    if(bl[T].R < n)
    {
        T ++;
        bl[T].L = bl[T - 1].R + 1;
        bl[T].R = n;
    }

    for(int i = 1; i <= T; i ++ ) 
    {
        bl[i].build();
        for(int j = bl[i].L; j <= bl[i].R; j ++ )
            pos[j] = i;
    }

    // for(int i = 1; i <= n; i ++ ) cout << sum[i] << ' ';
    // print();
    // change(1, n, 2);
    // print();

    m = read();

    while(m -- )
    {
        int op = read(), l = read(), r = read();
        if(op == 0)
        {
            ll k = read();
            change(l, r, k);
            if(r != n) add(r + 1, n, k * (r - l + 1));
        }
        else
        {
            printf("%lld\n", query(l, r));
        }
        // print();
    }

    return 0;
}