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

const int N = 2e6 + 10;
#define int ll

struct node
{
    int l, r;
    int siz, key;
    int L, R;
}t[N];
int root[N], cnt;
int n, m, q;

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + t[p].R - t[p].L + 1;
}

inline int New(int l, int r)
{
    t[++ cnt].L = l;
    t[cnt].R = r;
    t[cnt].siz = r - l + 1;
    t[cnt].key = rand();
    return cnt;
}

inline int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].key < t[y].key)
    {
        t[x].r = merge(t[x].r, y);
        pushup(x);
        return x;
    }
    else 
    {
        t[y].l = merge(x, t[y].l);
        pushup(y);
        return y;
    }
}

inline void split(int p, int k)
{
    if(k >= t[p].R - t[p].L + 1) return;
    int w = t[p].L + k - 1;
    int q = New(w + 1, t[p].R);
    t[p].R = w;
    t[p].r = merge(q, t[p].r);
    pushup(p);
}

inline void split(int p, int siz, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(t[t[p].l].siz >= siz) 
        {
            y = p;
            split(t[p].l, siz, x, t[y].l);
        }
        else
        {
            split(p, siz - t[t[p].l].siz);
            x = p;
            split(t[p].r, siz - t[t[p].l].siz - (t[p].R - t[p].L + 1), t[x].r, y);
        }
        pushup(p);
    }
}

int x, y, z, _x, _y, _z;
signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), q = read();
    for(int i = 1; i <= n; i ++ )
        root[i] = New((i - 1) * m + 1, i * m - 1);

    for(int i = 1; i <= n; i ++ )
        root[n + 1] = merge(root[n + 1], New(i * m, i * m));
    
    while(q -- )
    {
        int a = read(), b = read();
        if(b != m)
        {
            split(root[a], b - 1, x, y);
            split(y, 1, y, z);
            printf("%lld\n", t[y].L);
            
            split(root[n + 1], a - 1, _x, _y);
            split(_y, 1, _y, _z);

            root[a] = merge(x, merge(z, _y));
            root[n + 1] = merge(_x, merge(_z, y));
        }
        else
        {
            split(root[n + 1], a - 1, x, y);
            split(y, 1, y, z);
            printf("%lld\n", t[y].L);
            root[n + 1] = merge(x, merge(z, y));
        }
    }

    return 0;
}