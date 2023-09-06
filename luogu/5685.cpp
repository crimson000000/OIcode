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
int tr[N][27], fail[N], len[N];
int cnt[N][2];
int idx;
int n, m, slen;
char a[N], b[N];
int pos, cur;

inline int getfail(int x, int i)
{
    while(i - len[x] < 1 || a[i - len[x] - 1] != a[i]) x = fail[x];
    return x;
}

inline void insert(int i, int op)
{
    pos = getfail(cur, i);
    int u = a[i] - 'A';
    // if(a[i] == '$') u = 26;
    if(!tr[pos][u])
    {
        fail[++ idx] = tr[getfail(fail[pos], i)][u];
        tr[pos][u] = idx;
        len[idx] = len[pos] + 2;
    }
    cur = tr[pos][u];
    cnt[cur][op] ++;
}

inline void build()
{
    len[1] = -1, len[0] = 0;
    fail[0] = 1;
    idx = 1;
    for(int i = 1; i <= slen; i ++ ) insert(i, i <= n);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s%s", a + 1, b + 1);
    n = strlen(a + 1), m = strlen(b + 1);
    slen = n;
    a[++ slen] = 'A' + 26;
    for(int i = 1; i <= m; i ++ )
        a[++ slen] = b[i];

    build();

    for(int i = idx; i >= 0; i -- ) cnt[fail[i]][0] += cnt[i][0], cnt[fail[i]][1] += cnt[i][1];
    
    ll ans = 0;
    for(int i = 2; i <= idx; i ++ )
        ans = (ans + (ll)cnt[i][0] * cnt[i][1]);

    cout << ans << endl;

    return 0;
}