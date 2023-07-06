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
    int val, id, dis;
    int fa;
}t[N];
int cnt;

inline void init()
{
    memset(t, 0, sizeof t);
    cnt = 0;
}

inline int find(int x)
{
    if(t[x].fa != x) t[x].fa = find(t[x].fa);
    return t[x].fa;
}

inline int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].val < t[y].val) swap(x, y);
    
    t[x].r = merge(t[x].r, y);
    t[t[x].r].fa = x;

    if(t[t[x].r].dis > t[t[x].l].dis) swap(t[x].l, t[x].r);
    t[x].dis = t[t[x].r].dis + 1;
    return x;
}

int n, m;

inline int weak(int x)
{
    t[x].val >>= 1;
    int rt = merge(t[x].l, t[x].r);
    t[x].l = t[x].r = t[x].dis = 0;
    return t[x].fa = t[rt].fa = merge(x, rt);
}

void work(int x, int y)
{
    x = find(x), y = find(y);
    if(x == y)
    {
        puts("-1");
        return;
    }
    int l = weak(x), r = weak(y);
    t[l].fa = t[r].fa = merge(l, r);
    printf("%d\n", t[t[l].fa].val);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    while(scanf("%d", &n) == 1)
    {
        init();
        t[0].dis = -1;

        for(int i = 1; i <= n; i ++ )
        {
            t[i].val = read();
            t[i].fa = i;
        }

        m = read();
        while(m -- )
        {
            int x = read(), y = read();
            work(x, y);
        }
    }

    return 0;
}