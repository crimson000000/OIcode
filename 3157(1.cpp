#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;
typedef long double ld;

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
struct ele
{
    // a is time, b is val, c is pos
    int a, b, c;
    ll ans;
}e[N];
int n, m;
int a[N], pos[N];

inline bool cmpa(ele a, ele b)
{
    return a.a < b.a; 
}

inline bool cmpb(ele a, ele b)
{
    return a.b < b.b;
}

inline bool cmpc(ele a, ele b)
{
    return a.c < b.c;
}

struct ta
{
    int c[N];
    #define lowbit(x) x & -x
    inline void add(int x, int val)
    {
        for(; x <= n; x += lowbit(x)) c[x] += val;
    }

    inline void clear(int x)
    {
        for(; x <= n; x += lowbit(x)) c[x] = 0;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }
} bit;

ll ans;
inline void cdq(int l, int r)
{
    if(l == r) return;
    int mid = l + r >> 1;
    
    sort(e + l, e + r + 1, cmpa);
    cdq(l, mid), cdq(mid + 1, r);

    sort(e + l, e + mid + 1, cmpb);
    sort(e + mid + 1, e + r + 1, cmpb);
    
    int i, j;
    for(i = l, j = mid + 1; i <= mid; i ++ )
    {
        while(j <= r && e[j].b <= e[i].b)
        {
            bit.add(e[j].c, 1);
            j ++;
        }
        e[i].ans += bit.query(n) - bit.query(e[i].c);
    }

    for(int i = mid + 1; i <= r; i ++ ) bit.clear(e[i].c);

    for(i = mid, j = r; i >= l; i -- )
    {
        while(j >= mid + 1 && e[j].b >= e[i].b)
        {
            bit.add(e[j].c, 1);
            j --;
        }
        e[i].ans += bit.query(e[i].c);
    }

    for(int i = mid + 1; i <= r; i ++ ) bit.clear(e[i].c);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\noip\\in.in", "r", stdin);
        freopen("D:\\noip\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= n; i ++ ) 
    {
        a[i] = read();
        pos[a[i]] = i;
        e[i].b = a[i], e[i].c = i;
    }

    for(int i = 1; i <= m; i ++ )
    {
        int v = read();
        e[pos[v]].a = i;
    }

    int timmmm = m;
    for(int i = 1; i <= n; i ++ ) 
        if(!e[i].a)
            e[i].a = ++ timmmm;

    sort(e + 1, e + n + 1, cmpa);

    cdq(1, n);

    sort(e + 1, e + n + 1, cmpa);

    for(int i = n; i; i -- )
    {
        ans += bit.query(a[i]);
        bit.add(a[i], 1);
    }

    for(int i = 1; i <= m; i ++ )
    {
        printf("%lld\n", ans);
        ans -= e[i].ans;
    }

    return 0;
}
