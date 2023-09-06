#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int h[N], e[2 * N], ne[N * 2], idx;
int fa[N][18], d[N];
int n, m;

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs_for_father(int u, int father)
{
    fa[u][0] = father, d[u] = d[father] + 1;
    for(int i = 1; i < 18; i ++ )
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == father) continue;
        dfs_for_father(j, u);
    }
}

int lca(int x, int y)
{
    if(d[x] > d[y]) swap(x, y);
    for(int i = 17; i >= 0; i -- )
        if(d[fa[y][i]] >= d[x])
            y = fa[y][i];
    if(x == y) return x;
    for(int i = 17; i >= 0; i -- )
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

#define y second
#define x first
typedef pair<int, int> PII;
struct node
{
    int l, r;
    PII val;
}t[N * 70];
int cnt, root[N];
PII max(PII a, PII b)
{
    if(a.x > b.x) return a;
    else if(a.x == b.x)
    {
        if(a.y >= b.y) return b;
        else return a;
    }
    else return b;
}

void pushup(int p)
{
    t[p].val = max(t[t[p].l].val, t[t[p].r].val);
}

void change(int l, int r, int &p, int pos, int val)
{
    if(!p) p = ++ cnt;
    if(l == r)
    {
        t[p].val.x += val;
        t[p].val.y = pos;
        return;
    }
    int mid = l + r >> 1;
    if(pos <= mid) change(l, mid, t[p].l, pos, val);
    else change(mid + 1, r, t[p].r, pos, val);
    pushup(p);
}

void merge(int &a, int b, int l = 1, int r = N)
{
    if(!a || !b) a |= b;
    else if(l == r)
        t[a].val.x += t[b].val.x;
    else
    {
        int mid = l + r >> 1;
        merge(t[a].l, t[b].l, l, mid);
        merge(t[a].r, t[b].r, mid + 1, r);
        pushup(a);
    }
}

#undef y
#undef x

int ans[N];
void dfs_for_answer(int u)
{
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa[u][0]) continue;
        dfs_for_answer(j);
        merge(root[u], root[j]);
    }
    if(t[root[u]].val.first)
        ans[u] = t[root[u]].val.second;
}

int main()
{
    scanf("%d%d", &n, &m);
    memset(h, -1, sizeof h);

    for(int i = 0; i < n - 1; i ++ )
    {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a, b), add(b, a);
    }

    dfs_for_father(1, 0);

    while(m -- )
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        
        change(1, N, root[a], c, 1);
        change(1, N, root[b], c, 1);
        change(1, N, root[lca(a, b)], c, -1);
        change(1, N, root[fa[lca(a, b)][0]], c, -1);
    }

    dfs_for_answer(1);
    for(int i = 1; i <= n; i ++ ) 
        cout << ans[i] << endl;
    return 0;
}