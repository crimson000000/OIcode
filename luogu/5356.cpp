#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;
typedef __int128 i128;

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

const int N = 1e6 + 10, M = 1e3 + 10;
int a[N], pos[N];
int tmp1[N], tmp2[N], tmp3[N];
int BL, T;

int n, m;
inline bool cmp(int x, int y)
{
    return a[x] < a[y];
}

inline void merge(int a[], int b[], int x, int y, int c[])
{
    int i = 1, j = 1, k = 1;
    while(i <= x && j <= y)
    {
        if(cmp(a[i], b[j])) c[k ++ ] = a[i ++ ];
        else c[k ++ ] = b[j ++ ];
    }
    while(i <= x) c[k ++ ] = a[i ++ ];
    while(j <= y) c[k ++ ] = b[j ++ ];
    return;
}

inline void merge1(int a[], int b[], int x, int y, int c[])
{
    int i = 1, j = 1, k = 1;
    while(i <= x && j <= y)
    {
        if(a[i] < b[j]) c[k ++ ] = a[i ++ ];
        else c[k ++ ] = b[j ++ ];
    }
    while(i <= x) c[k ++ ] = a[i ++ ];
    while(j <= y) c[k ++ ] = b[j ++ ];
    return;
}

struct Block
{
    int l, r;
    int h[M * 20];
    int tt;
    int add;

    inline void build()
    {
        tt = 0;
        for(int i = l; i <= r; i ++ ) h[++ tt] = i;
        sort(h + 1, h + tt + 1, [](int x, int y){
            return a[x] < a[y];
        });
    }

    inline void Add(int L, int R, int val)
    {
        if(L <= l && r <= R) add += val;
        else
        {
            L = max(l, L), R = min(r, R);
            int tt1 = 0, tt2 = 0;
            for(int i = L; i <= R; i ++ ) a[i] += val;
            for(int i = 1; i <= tt; i ++ )
                if(L <= h[i] && h[i] <= R)
                    tmp1[++ tt1] = h[i];
                else tmp2[++ tt2] = h[i];
            merge(tmp1, tmp2, tt1, tt2, h);
        }
    }

    inline void get(int L, int R, int to[], int &len)
    {
        len = 0;
        for(int i = 1; i <= tt; i ++ )
            if(L <= h[i] && h[i] <= R)
                to[++ len] = a[h[i]] + add;
    }

    inline int rk(int v)
    {
        v -= add;
        int L = 1, R = tt + 1;
        while(L < R)
        {
            int mid = L + R >> 1;
            if(a[h[mid]] < v) L = mid + 1;
            else R = mid;
        }
        return L - 1;
    }
}B[M];

inline void change(int l, int r, int w)
{
    if(pos[l] == pos[r])
    {
        B[pos[l]].Add(l, r, w);
    }
    else
    {
        for(int i = pos[l] + 1; i < pos[r]; i ++ ) 
            B[i].Add(l, r, w);
        B[pos[l]].Add(l, r, w);
        B[pos[r]].Add(l, r, w);
    }
}

int tt3;
inline int rk_insmall(int val)
{
    return lower_bound(tmp3 + 1, tmp3 + tt3 + 1, val) - tmp3 - 1;
}

inline int kth(int l, int r, int v)
{
    int res = 0;
    for(int i = pos[l] + 1; i < pos[r]; i ++ )
        res += B[i].rk(v);
    res += rk_insmall(v);
    return res + 1;
}

inline int query(int l, int r, int k)
{
    if(pos[l] == pos[r])
    {
        int len;
        B[pos[l]].get(l, r, tmp1, len);
        return tmp1[k];
    }
    else
    {
        int tt1, tt2;
        B[pos[l]].get(l, r, tmp1, tt1);
        B[pos[r]].get(l, r, tmp2, tt2);
        merge1(tmp1, tmp2, tt1, tt2, tmp3);
        tt3 = tt1 + tt2;
        // for(int i = 1; i <= tt3; i ++ ) 
        //     cout << tmp3[i] << ' ';
        // puts("");
        int L = -2147483647, R = 2147483647;
        while(L < R)
        {
            int mid = ((ll)L + R + 1) >> 1;
            if(kth(l, r, mid) <= k) L = mid;
            else R = mid - 1;
        }
        return L;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    T = sqrt(n) / max((int)log(n), 1), BL = n / T;

    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
    }

    for(int i = 1; i <= T; i ++ )
        B[i].l = (i - 1) * BL + 1, B[i].r = i * BL;
    
    if(B[T].r != n)
    {
        T ++;
        B[T].l = B[T - 1].r + 1;
        B[T].r = n;
    }

    for(int i = 1; i <= T; i ++ )
    {
        for(int j = B[i].l; j <= B[i].r; j ++ )
            pos[j] = i;
        B[i].build();
    }

    // for(int i = 1; i <= n; i ++ ) printf("%d ", pos[i]);
    // puts("");

    // for(int i = 1; i <= B[4].tt; i ++ )
    //     cout << B[4].h[i] << ' ';
    // puts("");

    // int tt1, tt2;
    // B[1].get(3, 8, tmp1, tt1);
    // B[2].Add(6, 10, 4);
    // B[2].get(3, 8, tmp2, tt2);
    // cout << tt2 << endl;
    // merge1(tmp1, tmp2, tt1, tt2, tmp3);
    // tt3 = tt1 + tt2;
    // for(int i = 1; i <= tt3; i ++ )
    //     cout << tmp3[i] << ' ';

    // cout << query(1, 10, 3) << endl;

    while(m -- )
    {
        int op = read(), l = read(), r = read(), k = read();
        if(op == 1)
        {
            if(r - l + 1 >= k) printf("%d\n", query(l, r, k));
            else puts("-1");
        }
        else change(l, r, k);
        // for(int i = 1; i <= T; i ++ )
        // {
        //     B[i].pushdown();
        //     for(int j = B[i].l; j <= B[i].r; j ++ )
        //         printf("%d ", a[j]);
        // }
        // puts("");
    }

    return 0;
}
