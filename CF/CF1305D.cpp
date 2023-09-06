// #define LOCAL
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
int h[N], e[N], ne[N], idx;
bitset<N> vis;
int din[N];
int n;

inline void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);

    n = read();
    for(int i = 1; i < n; i ++ )
    {
        int a = read(), b = read();
        add(a, b), add(b, a);
        din[a] ++;
        din[b] ++;
    }

    while(1)
    {
        int u = -1, v = -1;
        for(int i = 1; i <= n; i ++ )
        {
            if(din[i] == 1 && u == -1) u = i;
            else if(din[i] == 1 && v == -1) v = i;
        }
        
        if(u == -1 && v == -1)
        {
            for(int i = 1; i <= n; i ++ )
                if(!vis[i])
                {
                    printf("! %d\n", i);
                    fflush(stdout);
                    return 0;
                }
        }

        if(v == -1)
        {
            printf("! %d\n", u);
            fflush(stdout);
            return 0;
        }

        din[u] --, din[v] --;
        vis[u] = vis[v] = true;
        printf("? %d %d\n", u, v);
        fflush(stdout);
        int lc = read();
        
        if(lc == u || lc == v)
        {
            printf("! %d\n", lc);
            fflush(stdout);
            return 0;
        } 

        for(int i = h[u]; i != -1; i = ne[i]) din[e[i]] --;
        for(int i = h[v]; i != -1; i = ne[i]) din[e[i]] --;
    }

    return 0;
}