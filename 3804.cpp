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

const int N = 2e6 + 10;
char s[N];
int n;
ll ans;
struct suffixautomaton
{
    int link[N], tr[N][26];
    int len[N];
    int f[N];
    vector<int> G[N];
    int idx, last;

    inline void init()
    {
        memset(link, 0, sizeof link);
        memset(tr, 0, sizeof tr);
        memset(len, 0, sizeof len);
        idx = last = 0;
        for(int i = 0; i <= 2000000; i ++ ) G[i].clear();
        link[0] = -1;
    }

    inline void extend(char *s)
    {
        int n = strlen(s + 1);
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
                    link[q] = link[cur] = copy;
                }
            }
            last = cur;
        }

        for(int i = 1; i <= idx; i ++ ) G[link[i]].emplace_back(i);
    }

    inline void dfs(int u)
    {
        for(auto v : G[u])
        {
            dfs(v);
            f[u] += f[v];
        }
        if(f[u] > 1) ans = max(ans, (ll)f[u] * len[u]);
    }
}SAM;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    SAM.init();
    SAM.extend(s);
    SAM.dfs(0);

    cout << ans << endl;

    cout << SAM.idx << endl;

    return 0;
}
