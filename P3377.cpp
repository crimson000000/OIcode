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

const int N = 1e5 + 10;
struct node
{
    int l, r, fa;
    int dis, val;
}t[N];

int merge(int x, int y)
{
    if(!x || !y) return x + y;

    if(t[x].val > t[y].val || (t[x].val == t[y].val && x > y))
        swap(x, y);
    
    t[x].r = merge(t[x].r, y);
    t[t[x].r].fa = x;
    if(t[t[x].l].dis < t[t[x].r].dis)
        swap(t[x].l, t[x].r);
    
    t[x].dis = t[t[x].r].dis + 1;
    return x;
}

inline void pop(int x)
{
    t[x].val = -1;
    t[t[x].l].fa = t[x].l;
    t[t[x].r].fa = t[x].r;
    t[x].fa = merge(t[x].l, t[x].r);
}

int find(int x)
{
    if(t[x].fa != x) t[x].fa = find(t[x].fa);
    return t[x].fa;
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
        t[i].val = read();
        t[i].fa = i;
    }

    while(m -- )
    {
        int op = read(), x = read();
        if(op == 1)
        {
            int y = read();
            if(t[x].val == -1 || t[y].val == -1) continue;

            int pa = find(x), pb = find(y);
            if(pa == pb) continue;
            t[pa].fa = t[pb].fa = merge(pa, pb);
        }
        else
        {
            if(t[x].val == -1) puts("-1");
            else 
            {
                cout << t[find(x)].val << endl;
                pop(find(x));
            }
        }
    }
    
    return 0;
}
