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

const int N = 1e6 + 10;
struct tw
{
    ll in, out, b;
    bool operator < (const tw& a) const
    {
        return b < a.b;
    }
}a[N];
int n;

struct node
{
    int l, r;
    ll val;
    int key, siz;
}t[N];
int root, cnt;

inline int New(ll val)
{
    t[++ cnt].val = val;
    t[cnt].key = rand();
    t[cnt].siz = 1;
    return cnt;
}

inline void pushup(int p)
{
    t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
}

int merge(int x, int y)
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

void split(int p, ll val, int &x, int &y)
{
    if(!p) x = y = 0;
    else
    {
        if(t[p].val <= val)
        {
            x = p;
            split(t[p].r, val, t[x].r, y);
        }
        else
        {
            y = p;
            split(t[p].l, val, x, t[y].l);
        }
        pushup(p);
    }
}

int x, y, z;
inline void insert(ll val)
{
    split(root, val, x, y);
    root = merge(merge(x, New(val)), y);
}

inline void del(ll val)
{
    split(root, val - 1, x, y);
    split(y, val, y, z);
    y = merge(t[y].l, t[y].r);
    root = merge(merge(x, y), z);
}

inline ll getpre(ll val)
{
    split(root, val - 1, x, y);
    ll res;
    if(!t[x].siz) res = -1;
    else
    {
        int p = x;
        while(t[p].r) p = t[p].r;
        res = t[p].val;
    }
    root = merge(x, y);
    return res;
}

void ldr(int p)
{
    if(t[p].l) ldr(t[p].l);
    cout << t[p].val << ' ';
    if(t[p].r) ldr(t[p].r);
}

ll ans;
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i].out = read(), a[i].in = read(), a[i].b = read();
        ans += a[i].in * a[i].b;
        insert(a[i].out);
    }

    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);
    for(int i = 1; i <= n; i ++ )
    {
        ll pre = getpre(a[i].in);
        if(pre != -1) ans -= a[i].b * pre;
        if(pre != -1) del(pre);
    }

    cout << ans << endl;

    return 0;
}
