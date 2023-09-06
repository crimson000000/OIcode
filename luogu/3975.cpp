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
char s[N];
int type, k;
struct suffixautomaton
{
    int link[N], tr[N][26];
    int len[N];
    int idx, last;
    int f[N], siz[N];
    bitset<N> vis;
    vector<int> G[N];

    inline void init()
    {
        memset(link, 0, sizeof link);
        memset(tr, 0, sizeof tr);
        memset(len, 0, sizeof len);
        idx = last = 0;
        link[0] = -1;
    }

    inline void extend(char *s)
    {
        int n = strlen(s + 1);
        for(int i = 1; i <= n; i ++ )
        {
            int p = last, cur = ++ idx, c = s[i] - 'a';
            f[cur] = siz[cur] = 1;
            len[cur] = len[p] + 1;
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

        for(int i = 1; i <= idx; i ++ ) G[link[i]].emplace_back(i);
    }

    inline void dfs1(int u)
    {
        for(auto v : G[u])
        {
            dfs1(v);
            siz[u] += siz[v];
        }
        f[u] = siz[u];
    }

    inline int dfs2(int u)
    {
        if(vis[u]) return f[u];
        vis[u] = true;
        for(int i = 0; i < 26; i ++ )
        {
            int v = tr[u][i];
            if(!v) continue;
            f[u] += dfs2(v);
        }
        return f[u];
    }

    inline void build(int type)
    {
        if(!type)
        {
            for(int i = 0; i <= idx; i ++ ) f[i] = siz[i] = 1;
        }
        else dfs1(0);
        f[0] = siz[0] = 0;
        dfs2(0);
    }

    inline void query(int u, int k)
    {
        if(k > f[u]) 
        {
            puts("-1");
            return;
        }
        if(k <= siz[u]) return;
        k -= siz[u];
        for(int i = 0; i < 26; i ++ )
        {
            int v = tr[u][i];
            if(!v) continue;
            if(k > f[v]) k -= f[v];
            else 
            {
                putchar(i + 'a');
                query(v, k);
                return;
            }
        }
    }
}SAM;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    type = read(), k = read();
    SAM.init();
    SAM.extend(s);
    SAM.build(type);
    SAM.query(0, k);

    return 0;
}
