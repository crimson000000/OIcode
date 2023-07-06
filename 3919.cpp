#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
struct segment
{
    int l, r;
    int dat;
}t[N * 4 + 20 * N];
int root[N], idx;
int a[N], n, m;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int build(int p, int l, int r)
{
    p = ++ idx;
    if(l == r)
    {
        t[p].dat = a[l];
        return idx;
    }
    int mid = l + r >> 1;
    t[p].l = build(t[p].l, l, mid); 
    t[p].r = build(t[p].r, mid + 1, r);
    return p;
}

int change(int p, int l, int r, int x, int val)
{
    int q = ++ idx;
    t[q] = t[p];
    if(l == r)
    {
        t[q].dat = val;
        return q;
    }
    int mid = l + r >> 1;
    if(x <= mid) t[q].l = change(t[q].l, l, mid, x, val);
    else t[q].r = change(t[q].r, mid + 1, r, x, val);
    return q;
}

int query(int p, int l, int r, int x)
{
    if(l == r) return t[p].dat;
    int mid = l + r >> 1;
    if(x <= mid) return query(t[p].l, l, mid, x);
    else return query(t[p].r, mid + 1, r, x);
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%d", &a[i]);
    }
    root[0] = build(0, 1, n);
    for(int i = 1; i <= m; i ++ )
    {
        int v, op, loc, val;
        scanf("%d%d%d",&v, &op, &loc);
        if(op == 1)
        {
            scanf("%d", &val);
            root[i] = change(root[v], 1, n, loc, val);
        }
        else
        {
            cout << query(root[v], 1, n, loc) << endl;
            root[i] = root[v];
        }
    }
}