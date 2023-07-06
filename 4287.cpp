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
int n, ans;
int tr[N][26], fail[N], trans[N];
int len[N], idx;
int cur, pos;

inline int getfail(int x, int i)
{
    while(i - len[x] < 1 || s[i - len[x] - 1] != s[i]) x = fail[x];
    return x;
}

inline void build(int n)
{
    len[1] = -1, fail[0] = 1;
    idx = 1;
    for(int i = 1; i <= n; i ++ )
    {
        pos = getfail(cur, i);
        int u = s[i] - 'a';
        if(!tr[pos][u])
        {
            fail[++ idx] = tr[getfail(fail[pos], i)][u];
            tr[pos][u] = idx;
            len[idx] = len[pos] + 2;
            if(len[idx] <= 2) trans[idx] = fail[idx];
            else
            {
                int tmp = trans[cur];
                while(s[i - len[tmp] - 1] != s[i] || ((len[tmp] + 2) << 1) > len[idx])
                    tmp = fail[tmp];
                trans[idx] = tr[tmp][u];
            }
        }
        cur = tr[pos][u];
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    scanf("%s", s + 1);
    build(n);

    for(int i = 1; i <= idx; i ++ )
        if(len[i] == (len[trans[i]] << 1) && (len[trans[i]] & 1) == 0)
            ans = max(ans, len[i]);

    cout << ans << endl;

    return 0;
}