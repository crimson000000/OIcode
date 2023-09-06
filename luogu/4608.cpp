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

const int N = 3020 + 10;
const ll base = 1e7; 
int nxt1[N][58], nxt2[N][58];
char a[N], b[N];
int n, m, k;

struct bigint
{
    vector<int> a;
    
    bigint() 
    {
        a.clear();
    }

    bigint(ll x)
    {
        while(x) a.push_back(x % base), x /= base;
    }

    bigint operator + (const bigint& b)
    {
        bigint c;
        ll t = 0;
        for(int i = 0; i < a.size() || i < b.a.size() || t; i ++ )
        {
            if(i < a.size()) t += a[i];
            if(i < b.a.size()) t += b.a[i];
            c.a.push_back(t % base);
            t /= base;
        }
        
        return c;
    }

    inline void print()
    {
        cout << a.back();
        for(int i = int(a.size()) - 2; i >= 0; i -- )
            printf("%07d", a[i]);
        if(a.size() == 0) printf("0");
    }
};

inline void build(char *s, int nxt[][58], int n)
{
    for(int i = 0; i < 58; i ++ ) nxt[n][i] = -1;
    for(int i = n; i >= 0; i -- )
    {
        for(int j = 0; j < 58; j ++ )
            nxt[i - 1][j] = nxt[i][j];
        nxt[i - 1][s[i] - 'A'] = i;
    }
}

char stk[N];
int tt;
inline void dfs1(int x, int y)
{
    printf("%s\n", stk + 1);
    for(int i = 0; i < 58; i ++ )
    {
        if(nxt1[x][i] == -1 || nxt2[y][i] == -1) continue;
        stk[++ tt] = i + 'A';
        dfs1(nxt1[x][i], nxt2[y][i]);
        stk[tt -- ] = ' ';
    }
}

bigint f[N][N];
bitset<N> vis[N];
inline void dfs2(int x, int y)
{
    if(vis[x][y]) return;
    vis[x][y] = true;
    f[x][y] = bigint(1);
    for(int i = 0; i < 58; i ++ )
    {
        if(nxt1[x][i] == -1 || nxt2[y][i] == -1) continue;
        dfs2(nxt1[x][i], nxt2[y][i]);
        f[x][y] = f[x][y] + f[nxt1[x][i]][nxt2[y][i]];
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    scanf("%s%s", a + 1, b + 1);

    build(a, nxt1, n);
    build(b, nxt2, m);

    k = read();
    if(k) dfs1(0, 0);
    dfs2(0, 0);

    f[0][0].print();

    return 0;
}