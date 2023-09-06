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
int n;
ll ans;

inline ll max(ll a, ll b)
{
    return a < b ? b : a;
}

namespace PAM
{
    int tr[N][26], fail[N];
    int cnt[N], len[N];
    int idx, cur, pos;

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
            }
            cur = tr[pos][u];
            cnt[cur] ++;
        }
    }

    inline void topsort()
    {
        for(int i = idx; i >= 0; i -- ) cnt[fail[i]] += cnt[i];
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    PAM::build(n);
    PAM::topsort();

    using namespace PAM;
    for(int i = 0; i <= idx; i ++ ) ans = max(ans, (ll)len[i] * cnt[i]);

    printf("%lld", ans);

    return 0;
}