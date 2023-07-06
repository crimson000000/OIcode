#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int N = 1e5 + 10;

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

int p[N];

struct segment
{
    int l, r;
    int cnt, id;
}t[3200010];
int idx, root[N];

int find(int x)
{
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}

inline void pushup(int p)
{
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
}

int insert(int q, int l, int r, int x, int i)
{
    if(!q) q = ++ idx;
    if(l == r)
    {
        t[q].cnt ++;
        t[q].id = i;
        return q;
    }
    int mid = l + r >> 1;
    if(x <= mid) t[q].l = insert(t[q].l, l, mid, x, i);
    else t[q].r = insert(t[q].r, mid + 1, r, x, i);
    pushup(q);
    return q;
}

int query(int p, int l, int r, int kth)
{
    int ans;
    if(t[p].cnt < kth || !p) return 0;
    if(l == r) return t[p].id;
    int mid = l + r >> 1;
    if(t[t[p].l].cnt >= kth) ans = query(t[p].l, l, mid, kth);
    else ans = query(t[p].r, mid + 1, r, kth - t[t[p].l].cnt);
    return ans;
}

int merge(int x, int y, int l, int r)
{
    if(!x) return y;
    if(!y) return x;
    else if(l == r)
    {
        t[x].cnt += t[y].cnt;
        if(t[y].id) t[x].id = t[y].id;
        return x;
    }
    else
    {
        int mid = l + r >> 1;        
        t[x].l = merge(t[x].l, t[y].l, l, mid);
        t[x].r = merge(t[x].r, t[y].r, mid + 1, r);
        pushup(x);
        return x;
    }
}

int n, m, q;

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif
    n = read(), m = read();
    for(int i = 1; i <= n; i ++ )
    {
        p[i] = i;
        int x = read();
        root[i] = insert(root[i], 1, n, x, i);
    }

    while(m -- )
    {
        int a = read(), b = read();
        if(find(b) == find(a)) continue;
        p[find(b)] = find(a);
        root[find(a)] = merge(root[find(a)], root[find(b)], 1, n);
    }
    q = read();

    while(q -- )
    {
        char op[2];
        int x, y;
        scanf("%s", op);
        x = read(), y = read();
        if(op[0] == 'Q')
        {
            int ans = query(root[find(x)], 1, n, y);
            if(!ans) puts("-1");
            else cout << ans << endl;
        }
        else
        {
            x = find(x), y = find(y);
            if(x == y) continue;
            p[y] = x;
            root[find(x)] = merge(root[x], root[y], 1, n);
        }
    }
   
    return 0;
}