#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

using ld = long double;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 2010;
const ld INF = 1e100;
ld f[N][N], val[N];
int tr[N][10], idx = 0;
int fail[N];
int sum[N];
int n, m;
char s[N], t[N];

inline void insert(char *s, ld v)
{
    int p = 0;
    for(int i = 1; s[i]; i ++ )
    {
        int u = s[i] - '0';
        if(!tr[p][u]) tr[p][u] = ++ idx;
        p = tr[p][u];
    } 
    sum[p] ++;
    val[p] += v;
}

queue<int> q;
inline void build()
{
    for(int i = 0; i < 10; i ++ )
        if(tr[0][i])
            q.push(tr[0][i]);
    while(q.size())
    {
        int u = q.front();
        q.pop();

        sum[u] += sum[fail[u]];
        val[u] += val[fail[u]];

        for(int i = 0; i < 10; i ++ )
        {
            int p = tr[u][i];
            if(!p) tr[u][i] = tr[fail[u]][i];
            else
            {
                fail[p] = tr[fail[u]][i];
                q.push(p);
            }
        }
    }
}

PII pre[N][N];
char res[N];
inline bool check(ld mid)
{
    for(int i = 0; i <= idx; i ++ )
        val[i] -= mid * sum[i];

    for(int i = 0; i <= n; i ++ )
        for(int j = 0; j <= idx; j ++ )
            f[i][j] = -INF;
    
    f[0][0] = 0;

    for(int i = 0; i < n; i ++ )
        for(int u = 0; u <= idx; u ++ )
            if(f[i][u] > -1e99)
                for(int c = 0; c < 10; c ++ )
                    if(s[i] == '.' || c + '0' == s[i])
                    {
                        // cout << "yeah" << endl;
                        int p = tr[u][c];
                        if(f[i + 1][p] < f[i][u] + val[p])
                        {
                            f[i + 1][p] = f[i][u] + val[p];
                            pre[i + 1][p] = {u, c};
                        }
                    }

    for(int i = 0; i <= idx; i ++ ) val[i] += mid * sum[i];

    ld ans = -INF;
    int node = 0;
    for(int i = 0; i <= idx; i ++ )
        if(ans < f[n][i])
            ans = f[n][i], node = i;
    
    for(int i = n, now = node; i; i -- )
        res[i] = pre[i][now].second + '0', now = pre[i][now].first;

    // cout << ans << endl;
    
    return f[n][node] > 0;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    n = read(), m = read();
    scanf("%s", s);

    for(int i = 1; i <= m; i ++ )
    {
        scanf("%s", t + 1);
        ld x = read();
        x = log(x);
        insert(t, x);
    }

    build();

    ld l = 0, r = 1e9;
    while(r - l > 1e-6)
    {
        ld mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }

    // cout << exp(l) << endl;

    check(l);

    printf("%s", res + 1);

    return 0;
}
