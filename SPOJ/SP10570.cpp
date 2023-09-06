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

const int N = 2e4 + 10;
int n;
char s[20][N];

struct sam
{
    int link[N], tr[N][26];
    int len[N];
    int mx[N], mn[N];
    int order[N], cnt[N];
    int idx, lst;

    inline void init()
    {
        memset(link, 0, sizeof link);
        memset(tr, 0, sizeof tr);
        memset(len, 0, sizeof len);
        memset(mx, 0, sizeof mx);
        memset(mn, 0, sizeof mn);
        memset(order, 0, sizeof order);
        memset(cnt, 0, sizeof cnt);
        link[0] = -1;
        lst = idx = 0;
    }

    inline void build(char *s)
    {
        for(int i = 1; s[i]; i ++ )
        {
            int cur = ++ idx, p = lst, c = s[i] - 'a';
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
                    link[q] = link[cur] = copy;
                }
            }
            lst = cur;
        }
    }

    inline void topsort()
    {
        for(int i = 0; i <= idx; i ++ ) cnt[len[i]] ++, mn[i] = len[i];
        for(int i = 1; i <= n; i ++ ) cnt[i] += cnt[i - 1];
        for(int i = 0; i <= idx; i ++ ) order[cnt[len[i]] -- ] = i;
        // for(int i = 1; i <= idx -+; i ++ ) cout << order[i] << ' ';
    }

    inline void find(char *s)
    {
        int p = 0, l = 0;
        for(int i = 1; s[i]; i ++ )
        {
            int u = s[i] - 'a';
            if(tr[p][u]) p = tr[p][u], mx[p] = max(mx[p], ++ l);
            else
            {
                while(p != -1 && !tr[p][u]) p = link[p];
                if(p == -1) p = 0, l = 0;
                else
                {
                    l = len[p] + 1;
                    p = tr[p][u];
                    mx[p] = max(mx[p], l);
                }
            }
        }

        for(int i = idx + 1; i >= 1; i -- )
        {
            int u = order[i];
            int f = link[u];
            mx[f] = max(mx[f], min(mx[u], len[f]));
            mn[u] = min(mn[u], mx[u]);
            mx[u] = 0;
        }
    }
}SAM;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = 1;
    while(T -- )
    {
        int k = read();
        for(int i = 1; i <= k; i ++ )
            scanf("%s", s[i] + 1);

        SAM.init();
        SAM.build(s[1]);
        n = strlen(s[1] + 1);
        SAM.topsort();
        for(int i = 2; i <= k; i ++ ) SAM.find(s[i]);
        int ans = 0;
        for(int i = 0; i <= SAM.idx; i ++ ) ans = max(ans, SAM.mn[i]);

        cout << ans << endl;
    }

    return 0;
}