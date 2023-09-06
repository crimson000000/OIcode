#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

const int N = 2e5 + 10;
struct node
{
    int l, r, fa;
}t[N * 40];

int rootfa[N], rootdep[N], cnt, tot;
int n, m;

int build(int l, int r)
{
    int p = ++ cnt;
    if(l == r)
    {
        t[p].fa = ++ tot;
        return p;
    }
    int mid = l + r >> 1;
    t[p].l = build(l, mid);
    t[p].r = build(mid + 1, r);
    return p;
}

int change(int l, int r, int p, int pos, int val)
{
    int q = ++ cnt;
    t[q] = t[p];
    if(l == r)
    {
        t[q].fa = val;
        return q;
    }
    int mid = l + r >> 1;
    if(pos <= mid) t[q].l = change(l, mid, t[p].l, pos, val);
    else t[q].r = change(mid + 1, r, t[p].r, pos, val);
    return q;
}

int query(int l, int r, int p, int pos)
{
    if(l == r) return t[p].fa;
    int mid = l + r >> 1;
    if(pos <= mid) return query(l, mid, t[p].l, pos);
    else return query(mid + 1, r, t[p].r, pos);
}

int find(int p, int x)
{
    int fx = query(1, n, rootfa[p], x);
    if(fx != x) return find(p, fx);
    else return fx;
}

int merge(int p, int x, int y)
{
    x = find(p - 1, x);
    y = find(p - 1, y);
    if(x == y)
    {
        rootfa[p] = rootfa[p - 1];
        rootdep[p] = rootdep[p - 1];
    }    
    else
    {
        int dx = query(1, n, rootdep[p - 1], x);
        int dy = query(1, n, rootdep[p - 1], y);
        if(dx < dy)
        {
            rootfa[p] = change(1, n, rootfa[p - 1], x, y);
            rootdep[p] = rootdep[p - 1];
        }
        else if(dx > dy)
        {
            rootfa[p] = change(1, n, rootfa[p - 1], y, x);
            rootdep[p] = rootdep[p - 1];
        }
        else
        {
            rootfa[p] = change(1, n, rootfa[p - 1], x, y);
            rootdep[p] = change(1, n, rootdep[p - 1], y, dy + 1);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    rootfa[0] = build(1, n);
    
    for(int ver = 1; ver <= m; ver ++ )
    {
        int op, x, y;
        op = read();
        if(op == 1)
        {
            x = read(), y = read();
            merge(ver, x, y);
        }
        else if(op == 2)
        {
            x = read();
            rootfa[ver] = rootfa[x];
            rootdep[ver] = rootdep[x];
        }
        else
        {
            x = read(), y = read();
            rootfa[ver] = rootfa[ver - 1];
            rootdep[ver] = rootdep[ver - 1];
            int fx = find(ver, x), fy = find(ver, y);
            if(fx == fy) cout << 1 << endl;
            else cout << 0 << endl;
        }
    }
    
    return 0;
}
