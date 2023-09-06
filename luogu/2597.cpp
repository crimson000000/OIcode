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

const int N = 1e5 + 10, M = 2e5 + 10;
int h[N], e1[M], ne1[M], idx1;
int hs[N], e2[M], ne2[M], idx2;
int din[N];
int n;
int fa[N][20], dep[N], dad[N], siz[N];
queue<int> q;

void add1(int a, int b)
{
    e1[idx1] = b, ne1[idx1] = h[a], h[a] = idx1 ++;
}

void add2(int a, int b)
{
    e2[idx2] = b, ne2[idx2] = hs[a], hs[a] = idx2 ++;
}

int lca(int x, int y)
{
    if(x == y) return x;
    if(dep[x] < dep[y]) swap(x, y);
    for(int i = 18; i >= 0; i -- )
        if(dep[fa[x][i]] >= dep[y])
            x = fa[x][i];
    if(x == y) return x;
    for(int i = 18; i >= 0; i -- )
        if(fa[x][i] != fa[y][i])
            x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

void dfs(int u)
{
    siz[u] = 1;
    for(int i = hs[u]; i != -1; i = ne2[i])
    {
        int j = e2[i];
        dfs(j);
        siz[u] += siz[j];
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    //图论记得初始化啊啊啊啊啊啊
    memset(h, -1, sizeof h);
    memset(hs, -1, sizeof hs);
    memset(dad, -1, sizeof dad);

    n = read();

    for(int i = 1; i <= n; i ++ )
    {
        int a = read();
        while(a)
        {
            add1(a, i);
            din[i] ++;
            a = read();
        }
    }

    for(int i = 1; i <= n; i ++ )
        if(!din[i])
        {
            q.push(i);
            dad[i] = 0;
        }
    
    while(!q.empty())
    {
        int t = q.front();
        q.pop();
        add2(dad[t], t);
        fa[t][0] = dad[t], dep[t] = dep[dad[t]] + 1;
        for(int i = 1; i <= 18; i ++ )
            fa[t][i] = fa[fa[t][i - 1]][i - 1];

        for(int i = h[t]; i != -1; i = ne1[i])
        {
            int j = e1[i];
            if(dad[j] == -1) dad[j] = t;
            else dad[j] = lca(dad[j], t);
            din[j] --;
            if(!din[j]) q.push(j);
        }
    } 
    dfs(0);
    for(int i = 1; i <= n; i ++ ) cout << siz[i] - 1 << endl;

    return 0;
}
