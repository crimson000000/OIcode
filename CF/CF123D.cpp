#define LOCAL
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

const int N = 3e5 + 10;
char s[N];
int n;
ll ans;
struct SAM
{
    int tr[N][26], len[N];
    int link[N];
    ll f[N], g[N];
    int din[N];
    vector<int> G[N];
    int idx, last;

    inline void init()
    {
        link[0] = -1;
    }

    inline void build()
    {
        for(int i = 1; i <= n; i ++ )
        {
            int cur = ++ idx, p = last, c = s[i] - 'a';
            len[cur] = len[p] + 1;
            f[cur] = 1;
            while(p != -1 && !tr[p][c])
            {
                tr[p][c] = cur;
                p = link[p];
            }
            if(p == -1) link[cur] = 0;
            else
            {
                int q = tr[p][c];
                if(len[q] == len[p] + 1) link[cur] = q;
                else
                {
                    int copy = ++ idx;
                    len[copy] = len[p] + 1;
                    link[copy] = link[q];
                    for(int i = 0; i < 26; i ++ ) tr[copy][i] = tr[q][i];
                    while(p != -1 && tr[p][c] == q)
                    {
                        tr[p][c] = copy;
                        p = link[p];
                    }
                    link[cur] = link[q] = copy;
                }
            }
            last = cur;
        }

        for(int i = 1; i <= idx; i ++ ) G[link[i]].push_back(i);
        for(int i = 0; i <= idx; i ++ )
            for(int c = 0; c < 26; c ++ )
            {
                int v = tr[i][c];
                if(v) din[v] ++;
            }
    }

    inline void dfs(int u)
    {
        for(auto v : G[u])
        {
            dfs(v);
            f[u] += f[v];
        }
    }

    inline void bfs()
    {
        queue<int> q;
        q.push(0);
        g[0] = 1;
        while(q.size())
        {
            int u = q.front();
            q.pop();

            for(int i = 0; i < 26; i ++ )
            {
                int v = tr[u][i];
                if(!v) continue;
                din[v] --;
                g[v] += g[u];
                if(!din[v]) q.push(v);
            }
        }

        for(int i = 1; i <= idx; i ++ )
        {
            // cout << g[i] << ' ' << f[i] << endl;
            ans += g[i] * (f[i] + 1) * f[i] / 2;
        }
    }
}sam;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    sam.init();
    sam.build();
    sam.dfs(0);
    sam.bfs();

    cout << ans << endl;

    return 0;
}