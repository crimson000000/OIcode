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
int tr[N][4], len[N], fail[N], trans[N];
int idx;
int f[N];
int n, pos, cur, ans;
char s[N];

inline void init()
{
    idx = 1;
    cur = 1;
    ans = 0x3f3f3f3f;
    len[1] = -1, fail[0] = fail[1] = 1;
}

inline int to_num(char s)
{
    if(s == 'A') return 0;
    if(s == 'G') return 1;
    if(s == 'C') return 2;
    return 3;
}

inline int getfail(int x, int i)
{
    while(i - len[x] < 1 || s[i - len[x] - 1] != s[i]) x = fail[x];
    return x;
}

inline void build(int n)
{
    for(int i = 1; i <= n; i ++ )
    {
        int u = to_num(s[i]);
        pos = getfail(cur, i);
        if(!tr[pos][u])
        {
            fail[++ idx] = tr[getfail(fail[pos], i)][u];
            tr[pos][u] = idx;
            len[idx] = len[pos] + 2;
            if(len[idx] <= 2) trans[idx] = fail[idx];
            else
            {
                int tmp = trans[cur];
                while(((len[tmp] + 2) << 1) > len[idx] || s[i - len[tmp] - 1] != s[i]) 
                    tmp = fail[tmp];
                trans[idx] = tr[tmp][u];
            }
        }
        cur = tr[pos][u];
    }
}

queue<int> q;
inline void bfs()
{
    while(q.size()) q.pop();
    q.push(0);
    while(q.size())
    {
        int u = q.front();
        q.pop();
        ans = min(ans, f[u] + n - len[u]);
        for(int i = 0; i < 4; i ++ )
        {
            int v = tr[u][i];
            if(!v) continue;
            f[v] = min(f[u] + 1, f[trans[v]] + len[v] / 2 - len[trans[v]] + 1);
            q.push(v);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        init();
        scanf("%s", s + 1);
        n = strlen(s + 1);
        ans = n;

        build(n);
        f[0] = 1;
        for(int i = 2; i <= idx; i ++ ) f[i] = len[i];
        bfs();
        
        printf("%d\n", ans);
        for(int i = 0; i <= idx; i ++ )
        {
            fail[i] = trans[i] = len[i] = 0;
            for(int j = 0; j < 4; j ++ ) tr[i][j] = 0;
        }
    }

    return 0;
}
