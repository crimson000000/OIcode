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

const int N = 1e6 + 10;
char s[N];
ll ans;
int n;

struct SuffixAtm
{
    int tr[N][26], len[N];
    int link[N], siz[N];
    vector<int> G[N];
    int idx, lst;

    inline void init()
    {
        link[0] = -1;
    }

    inline void build()
    {
        for(int i = 1; i <= n; i ++ )
        {
            int p = lst, cur = ++ idx, c = s[i] - 'a';
            len[cur] = len[p] + 1;
            siz[cur] = 1;
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
                    link[copy] = link[q];
                    len[copy] = len[p] + 1;
                    for(int i = 0; i < 26; i ++ ) tr[copy][i] = tr[q][i];
                    while(p != -1 && tr[p][c] == q)
                    {
                        tr[p][c] = copy;
                        p = link[p];
                    }
                    link[q] = link[cur] = copy;
                }
            }
            lst = cur;
        }

        for(int i = 1; i <= idx; i ++ ) G[link[i]].push_back(i);
    }

    ll ans = 0;
    inline void dfs(int u)
    {
        ll tmp = 0;
        for(auto v : G[u])
        {
            dfs(v);
            tmp += (ll)siz[u] * siz[v];
            siz[u] += siz[v];
        }
        ans += tmp * 2 * len[u];
    }

    inline ll calc()
    {
        dfs(0);
        return ans;
    }
}SAM;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    reverse(s + 1, s + n + 1);
    SAM.init();
    SAM.build();
    cout << (ll)(n - 1) * n * (n + 1) / 2 - SAM.calc() << endl;

    return 0;
}