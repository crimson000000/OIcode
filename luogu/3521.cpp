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
int n;

struct segment
{
    int l, r;
    int cnt;
}t[N * 22];
int idx;
ll ans, u, v;

inline void pushup(int p)
{
    t[p].cnt = t[t[p].l].cnt + t[t[p].r].cnt;
}

int insert(int l, int r, int x)
{
    int p = ++ idx;
    t[p].cnt ++ ;
    if(l == r) return p;
    int mid = l + r >> 1;
    if(x <= mid) t[p].l = insert(l, mid, x);
    else t[p].r = insert(mid + 1, r, x);
    return p;
}

int merge(int x, int y, int l, int r)
{
    if(!x || !y) return x + y;
    if(l == r)
    {
        t[x].cnt += t[y].cnt;
        return x;
    }
    u += (ll)t[t[x].r].cnt * t[t[y].l].cnt;
    v += (ll)t[t[x].l].cnt * t[t[y].r].cnt;
    int mid = l + r >> 1;
    t[x].l = merge(t[x].l, t[y].l, l, mid);
    t[x].r = merge(t[x].r, t[y].r, mid + 1, r);
    pushup(x);
    return x;
}

int dfs()
{
    int val = read(), root;
    if(val == 0)
    {
        int l = dfs(), r = dfs();
        u = 0, v = 0;
        root = merge(l, r, 1, n);
        ans += min(u, v);
    }
    else root = insert(1, n, val);
    return root;
}

int main()
{
    #ifdef LOCAL
        freopen("in.in", "r", stdin);
        freopen("out.out", "w", stdout);
    #endif
    n = read();

    dfs();

    cout << ans << endl;

    return 0;
}