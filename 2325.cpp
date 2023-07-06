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

const int N = 1e5 + 10;
int n, lim;
int h[N], e[N], ne[N], idx;
int siz[N], b[N], cnt, rt[N];

struct Stack
{
    int stk[N];
    int tt;
    inline bool empty() {return tt == 0;}

    inline void clear() {tt = 0;}

    inline int size() {return tt;}

    inline int top() {return stk[tt];}

    inline void pop() {tt -- ;}

    inline void push(int x) {stk[++ tt] = x;}
}stk;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

void dfs(int u, int fa)
{
    int sz = stk.size();
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == fa) continue;
        dfs(j, u);
        siz[u] += siz[j];
        if(stk.size() - sz >= lim)
        {
            cnt ++;
            rt[cnt] = u;
            while(stk.size() > sz) b[stk.top()] = cnt, stk.pop();
        }
    }
    stk.push(u);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), lim = read();
    for(int i = 1; i < n; i ++ )
    {
        int u = read(), v = read();
        add(u, v), add(v, u);
    }

    dfs(1, 1);

    while(stk.size()) b[stk.top()] = cnt, stk.pop();
    cout << cnt << endl;
    for(int i = 1; i <= n; i ++ ) cout << b[i] << ' ';
    puts("");
    for(int i = 1; i <= cnt; i ++ ) cout << rt[i] << ' ';
    
    return 0;
}
