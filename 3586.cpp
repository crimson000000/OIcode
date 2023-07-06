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

const int N = 2e6 + 10;
int n, m;
int s[N];
struct fhq
{
    struct node
    {
        int l, r;
        int key;
        ll sum, val;
        int siz;
    }t[N];
    int root, cnt;

    int New(ll val)
    {
        t[++ cnt].siz = 1;
        t[cnt].val = val;
        t[cnt].key = rand();
        t[cnt].sum = val;
        return cnt;
    }

    inline void pushup(int p)
    {
        t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
        t[p].sum = t[t[p].l].sum + t[t[p].r].sum + t[p].val;
    }

    int merge(int x, int y)
    {
        if(!x || !y) return x + y;
        if(t[x].key > t[y].key)
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

    void del(int val)
    {
        split(root, val - 1, x, y);
        split(y, val, y, z);
        y = merge(t[y].l, t[y].r);
        root = merge(merge(x, y), z);
    }
}t;

int x, y, z;
int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    while(m -- )
    {
        char op[2];
        scanf("%s", op);
        if(op[0] == 'U')
        {
            int k = read(), a = read();
            t.insert(a);
            if(s[k]) t.del(s[k]);
            s[k] = a;
        }
        else
        {
            ll c = read(), v = read();
            t.split(t.root, v - 1, x, y);
            int r = c - t.t[y].siz;
            if(t.t[x].sum >= r * v) puts("TAK");
            else puts("NIE");
            t.root = t.merge(x, y);
        }
    }
    
    return 0;
}
