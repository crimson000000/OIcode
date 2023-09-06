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

const int N = 4e5 + 10;
char s[N], str[N];
struct ACAM
{
    int tr[N][26], val[N];
    int fail[N];
    int idx;

    inline void insert(char *s)
    {
        int len = strlen(s + 1);
        // cout << len << endl;
        int p = 0;
        for(int i = 1; i <= len; i ++ )
        {
            int u = s[i] - 'a';
            if(!tr[p][u]) tr[p][u] = ++ idx;
            p = tr[p][u];
        }
        val[p] ++;
    }

    inline void build()
    {
        queue<int> q;
        while(q.size()) q.pop();
        for(int i = 0; i < 26; i ++ )
            if(tr[0][i])
                q.push(tr[0][i]);
        while(q.size())
        {
            int u = q.front();
            q.pop();

            for(int i = 0; i < 26; i ++ )
            {
                int v = tr[u][i];
                if(!v) tr[u][i] = tr[fail[u]][i];
                else
                {
                    fail[v] = tr[fail[u]][i];
                    val[v] += val[fail[v]];
                    q.push(v);
                }
            }
        }
    }

    inline void query(char *s, int len, ll f[])
    {
        int p = 0;
        for(int i = 1; i <= len; i ++ )
        {
            int c = s[i] - 'a';
            p = tr[p][c];
            f[i] = val[p];
        }
    }
}AC, RAC;
int n, m;
ll f1[N], f2[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    m = read();
    for(int i = 1; i <= m; i ++ )
    {
        scanf("%s", str + 1);
        AC.insert(str);
        reverse(str + 1, str + strlen(str + 1) + 1);
        RAC.insert(str);
    }

    AC.build();
    RAC.build();
    
    AC.query(s, n, f1);
    reverse(s + 1, s + n + 1);
    RAC.query(s, n, f2);

    ll ans = 0;
    for(int i = 1; i <= n; i ++ )
        ans += f1[i] * f2[n - i];
    
    cout << ans << endl;

    return 0;
}