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
int tr[N >> 1][26], len[N], fail[N], idx;
int slink[N], diff[N];
int f[N], g[N], wh[N];
int n, m;
char s1[N], s2[N], s[N];
int ansl[N];

inline void init()
{
    len[1] = -1, fail[0] = 1;
    idx = 1;
} 

inline int getfail(int x, int i)
{
    while(i - len[x] < 1 || s[i - len[x] - 1] != s[i]) x = fail[x];
    return x;
}

int pos, cur;
inline void insert(int i)
{
    int u = s[i] - 'a';
    pos = getfail(cur, i);
    if(!tr[pos][u])
    {
        int x = ++ idx;
        len[x] = len[pos] + 2;
        fail[x] = tr[getfail(fail[pos], i)][u];
        tr[pos][u] = x;
        diff[x] = len[x] - len[fail[x]];
        if(diff[x] == diff[fail[x]])
            slink[x] = slink[fail[x]];
        else slink[x] = fail[x];
    }
    cur = tr[pos][u];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s%s", s1 + 1, s2 + 1);
    m = strlen(s1 + 1);
    n = m << 1;
    
    for(int i = 1; i <= n; i += 2) s[i] = s1[(i >> 1) + 1];
    for(int i = 2; i <= n; i += 2) s[i] = s2[i >> 1];

    init();

    memset(g, 0x3f, sizeof g);
    g[0] = 0;

    for(int i = 1; i <= n; i ++ )
    {
        insert(i);
        if(i % 2 == 0 && s[i] == s[i - 1] && g[i] > g[i - 2])
            g[i] = g[i - 2], ansl[i] = i - 2;
        for(int p = cur; p; p = slink[p])
        {
            // cout << p << endl;
            f[p] = i - len[slink[p]] - diff[p];
            if(diff[fail[p]] == diff[p] && g[f[p]] > g[f[fail[p]]])
                f[p] = f[fail[p]];
            if(i % 2 == 0 && g[i] > g[f[p]] + 1)
                g[i] = g[f[p]] + 1, ansl[i] = f[p];
        }
    }

    if(g[n] > 1e9) 
    {
        puts("-1");
        return 0;
    }

    printf("%d\n", g[n]);
    for(int i = n; i >= 1; i = ansl[i])
        if(i - ansl[i] != 2)
            printf("%d %d\n", (ansl[i] >> 1) + 1, i >> 1);

    return 0;
}