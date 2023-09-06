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

const int N = 1e6 + 10;
struct seg
{
    int l, r;
    int cnt;
    ll sum;
}t[N * 10];
int cnt, root[N];
int h[N], e[N], ne[N], idx;
int n;
int col[N];
ll ans[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
} 

void pushup(int p)
{
    t[p].cnt = max(t[t[p].l].cnt, t[t[p].r].cnt);
    t[p].sum = 0;
    if(t[t[p].l].cnt == t[p].cnt) t[p].sum += t[t[p].l].sum;
    if(t[t[p].r].cnt == t[p].cnt) t[p].sum += t[t[p].r].sum;
}

void change(int &p, int l, int r, int pos, int v)
{
    if(!p) p = ++ cnt;
    if(l == r) 
    {
        t[p].cnt += v;
        t[p].sum = l;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) change(t[p].l, l, mid, pos, v);
    else change(t[p].r, mid + 1, r, pos, v);
    pushup(p);
}

int merge(int p, int q, int l, int r)
{
    if(!p || !q) return p + q;
    if(l == r)
    {
        t[p].cnt += t[q].cnt;
        if(t[p].cnt) t[p].sum = l;
        return p;
    }
    int mid = l + r >> 1;
    t[p].l = merge(t[p].l, t[q].l, l, mid);
    t[p].r = merge(t[p].r, t[q].r, mid + 1, r);
    pushup(p);
    return p;
}

void dfs(int u, int fa)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int v = e[i];
        if(v == fa) continue;
        dfs(v, u);
        root[u] = merge(root[u], root[v], 1, n);
    }
    change(root[u], 1, n, col[u], 1);
    ans[u] = t[root[u]].sum;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read();
    for(int i = 1; i <= n; i ++ ) col[i] = read();
    
    for(int i = 1; i < n; i ++ ) 
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
    }

    dfs(1, 0);

    for(int i = 1; i <= n; i ++ ) printf("%lld ", ans[i]);

    return 0;
}