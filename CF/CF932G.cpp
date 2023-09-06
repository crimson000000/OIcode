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

const int N = 1.5e6 + 10, mod = 1e9 + 7;
int tr[N][26], fail[N], diff[N], slink[N], len[N];
int idx;
int f[N], g[N];
char s[N << 1], t[N << 1];
int n, pos, cur;

void init()
{
    idx = 1;
    len[1] = -1;
    fail[0] = 1;
}

inline int add(int a, int b)
{
    int c = a + b;
    while(c >= mod) c -= mod;
    return c;
}

inline int New(int l)
{
    idx ++;
    len[idx] = l;
    return idx;
}

inline int getfail(int x, int i)
{
    while(i - len[x] < 1 || s[i - len[x] - 1] != s[i]) x = fail[x];
    return x;
}

void insert(int i)
{
    pos = getfail(cur, i);
    int u = s[i] - 'a';
    if(!tr[pos][u])
    {
        int x = New(len[pos] + 2);
        fail[x] = tr[getfail(fail[pos], i)][u];
        tr[pos][u] = x;
        diff[x] = len[x] - len[fail[x]];
        if(diff[x] == diff[fail[x]])
            slink[x] = slink[fail[x]];
        else slink[x] = fail[x];
    }
    cur = tr[pos][u];
}

void build(int n)
{
    init();
    f[0] = 1;
    for(int i = 1; i <= n; i ++ )
    {
        insert(i);
        for(int x = cur; x > 1; x = slink[x])
        {
            g[x] = f[i - len[slink[x]] - diff[x]];
            if(diff[x] == diff[fail[x]]) g[x] = add(g[x], g[fail[x]]);
            if((i & 1) == 0) f[i] = add(f[i], g[x]);
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", t + 1);
    n = strlen(t + 1);

    for(int i = 1, m = 0; i <= n; i ++ )
    {
        s[++ m] = t[i], s[++ m] = t[n - i + 1];
    }
    
    build(n);

    cout << f[n] << endl;

    return 0;
}