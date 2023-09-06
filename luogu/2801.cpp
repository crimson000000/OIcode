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

const int N = 1e6 + 10, M = 1e4 + 10;
int a[N], pos[N];
int T, BL;
struct block
{
    int l, r;
    vector<int> h;
    int add;

    inline void pushdown()
    {
        for(int i = l; i <= r; i ++ ) a[i] += add;
        add = 0;
    }

    inline void build()
    {
        h.clear();
        for(int i = l; i <= r; i ++ ) h.emplace_back(a[i]);
        sort(h.begin(), h.end());
    }

    inline int uppernum(int val)
    {
        val -= add;
        return h.end() - lower_bound(h.begin(), h.end(), val);
    }
}B[M];
int n, m;

inline void change(int l, int r, int val)
{
    if(pos[l] == pos[r])
    {
        B[pos[l]].pushdown();
        for(int i = l; i <= r; i ++ ) a[i] += val;
        B[pos[l]].build();
    }
    else
    {
        for(int i = pos[l] + 1; i < pos[r]; i ++ ) 
            B[i].add += val;
        
        B[pos[l]].pushdown();
        for(int i = l; i <= B[pos[l]].r; i ++ )
            a[i] += val;
        B[pos[l]].build();

        B[pos[r]].pushdown();
        for(int i = B[pos[r]].l; i <= r; i ++ )
            a[i] += val;
        B[pos[r]].build();
    }
}

inline int query(int l, int r, int val)
{
    int res = 0;
    if(pos[l] == pos[r])
    {
        B[pos[l]].pushdown();
        for(int i = l; i <= r; i ++ ) 
            if(a[i] >= val)
                res ++;
        return res;
    }
    else
    {
        for(int i = pos[l] + 1; i < pos[r]; i ++ )
            res += B[i].uppernum(val);
        
        B[pos[l]].pushdown();
        B[pos[r]].pushdown();

        for(int i = l; i <= B[pos[l]].r; i ++ )
            if(a[i] >= val) 
                res ++;
        
        for(int i = B[pos[r]].l; i <= r; i ++ )
            if(a[i] >= val)
                res ++;
        return res;
    }
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    T = sqrt(n), BL = n / T;
    for(int i = 1; i <= n; i ++ ) a[i] = read();

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

    while(m -- )
    {
        char op[10];
        scanf("%s", op);
        if(op[0] == 'M')
        {
            int l = read(), r = read(), w = read();
            change(l, r, w);
        }
        else
        {
            int l = read(), r = read(), w = read();
            printf("%d\n", query(l, r, w));
        }
    }

    return 0;
}
