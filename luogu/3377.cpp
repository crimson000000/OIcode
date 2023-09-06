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
    int val, dis, fa;
}t[N];

inline int find(int x)
{
    if(t[x].fa != x) t[x].fa = find(t[x].fa);
    return t[x].fa;
}

inline int merge(int x, int y)
{
    if(!x || !y) return x + y;
    if(t[x].val > t[y].val || (t[x].val == t[y].val && x > y)) 
        swap(x, y);

    t[x].r = merge(t[x].r, y);
    t[t[x].r].fa = x;

    if(t[t[x].r].dis > t[t[x].l].dis) swap(t[x].l, t[x].r);
    t[x].dis = t[t[x].r].dis + 1;
    return x;
}

inline int gettop(int x)
{
    return t[find(x)].val;
}

inline void del(int x)
{
    t[x].val = -1;
    t[t[x].l].fa = t[x].l, t[t[x].r].fa = t[x].r;
    t[x].fa = merge(t[x].l, t[x].r);
}

int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    t[0].dis = -1;
    for(int i = 1; i <= n; i ++ )
    {
        int val = read();
        t[i].val = val;
        t[i].fa = i;
    }

    while(m -- )
    {
        int op = read();
        if(op == 1)
        {
            int x = read(), y = read();
            if(t[x].val == -1 || t[y].val == -1) continue;
            x = find(x), y = find(y);
            if(x == y) continue;
            t[x].fa = t[y].fa = merge(x, y);
        }
        else
        {
            int x = read();
            if(t[x].val == -1)
            {
                puts("-1");
                continue;
            }
            int val = gettop(x);
            printf("%d\n", val);
            del(find(x));
        }
    }

    return 0;
}