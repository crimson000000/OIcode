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
int h[N], e[N], ne[N], idx;
int din[N], dout[N];
int n, m, cnt;
vector<int> root;
int mp[N];

struct E
{
    int u, v;
}E[N];

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int fa[N];
void dfs(int u, int f)
{
    fa[u] = f;
    for(int i = h[u]; i != -1; i = ne[i])
    {
        int j = e[i];
        if(j == f) continue;
        dfs(j, u);
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        int a = read(), b = read();
        din[b] ++; 
        E[i] = {a, b};
    }

    cnt = n;
    for(int i = 1; i <= n; i ++ )
        if(!din[i])
        {
            root.push_back(i);
            mp[i] = ++ cnt;
        }

    printf("%d\n", cnt);
    for(auto u : root)
        printf("%d %d %d\n", mp[u], u, u);
    
    for(int i = 1; i <= m; i ++ )
        printf("%d %d %d\n", E[i].u, E[i].v, E[i].v);

    return 0;
}

// int rt, cnt = 0;
    // for(int i = 1; i <= n; i ++ )
    //     if(!din[i])
    //         cnt ++;
    
    // if(cnt == 1)
    // {
    //     for(int i = 1; i <= n; i ++ )
    //         if(!din[i])
    //         {
    //             rt = i;
    //             dfs(rt, rt);
    //             break;
    //         }
    // }
    // else
    // {
    //     for(int i = 1; i <= n; i ++ )
    //     {
    //         if(!dout[i])
    //         {
    //             rt = i;
    //             dfs(rt, rt);
    //             break;
    //         }
    //     }
    // }

    // printf("%d\n", n + 1);
    // printf("%d %d %d\n", n + 1, rt, rt);
    // for(int i = 1; i <= n; i ++ )
    // {
    //     if(i == rt) continue;
    //     printf("%d %d %d\n", fa[i], i, i);
    // }