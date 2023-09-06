#define LOCAL
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

using PII = pair<ll, ll>;

const int N = 110;
vector<int> cir[N];
int p[N];
char s[N];
int n;
bitset<N> vis;
int pcnt;

inline void dfs1(int u)
{
    if(vis[u]) return;
    cir[pcnt].push_back(u);
    vis[u] = true;
    dfs1(p[u]);
}

inline void dfs(int now)
{
    if(now == pcnt + 1)
    {
        int sum = 0;
        for(int i = 1; i <= n; i ++ )
        {
            sum += ((s[i] == '(') ? 1 : -1);
            if(sum < 0) return;
        }
        if(sum > 0) return;
        puts(s + 1);
        exit(0);
    }

    if(cir[now].size() == 2)
    {
        s[cir[now][0]] = '(';
        s[cir[now][1]] = ')';
        dfs(now + 1);
        return;
    }

    for(int i = 0; i < int(cir[now].size()); i ++ )
    {
        if(i & 1) s[cir[now][i]] = ')';
        else s[cir[now][i]] = '(';
    }
    dfs(now + 1);
    for(int i = 0; i < int(cir[now].size()); i ++ )
    {
        if(!(i & 1)) s[cir[now][i]] = ')';
        else s[cir[now][i]] = '(';
    }
    dfs(now + 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) p[i] = read();

    for(int i = 1; i <= n; i ++ )
        if(!vis[i])
        {
            pcnt ++;
            dfs1(i);
        }

    dfs(1);

    return 0;
} 