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
struct node
{
    int l, r;
    int siz, val;
    int key;
}t[N];
int cnt, root;
int n, mx;
int a[N], ans;

inline int New(int val)
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

void split(int p, int val, int &x, int &y)
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
void insert(int val)
{
    split(root, val, x, y);
    root = merge(merge(x, New(val)), y);
}

inline void del(int val)
{
    split(root, val - 1, x, y);
    split(y, val, y, z);
    y = merge(t[y].l, t[y].r);
    root = merge(merge(x, y), z);
}

inline int getpre(int val)
{
    split(root, val - 1, x, y);
    int p = x;
    while(t[p].r) p = t[p].r;
    int ret = t[p].val;
    root = merge(x, y);
}

inline int getmin()
{
    int p = root;
    while(t[p].l) p = t[p].l;
    return t[p].val;
}

inline int getmax()
{
    int p = root;
    while(t[p].r) p = t[p].r;
    return t[p].val;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    mx = read(), n = read();
    for(int i = 1; i <= n; i ++ )
    {
        a[i] = read();
        insert(a[i]);
    }

    while(t[root].siz)
    {
        int val = getmax();
        del(val);
        int maxx = getmin();
        if(val + maxx <= mx) del(maxx);
        ans ++; 
    }

    cout << ans << endl;

    return 0;
}