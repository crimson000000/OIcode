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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1100;
ll n, m, mod;
int ne[N], match[N][N];
char s[N];

struct mat
{
    ll a[50][50];
    int n, m;

    ll* operator [] (int x)
    {
        return a[x];
    }

    void init()
    {
        memset(a, 0, sizeof a);
    }

    mat operator * (const mat& M) const
    {
        mat tmp;
        tmp.init();
        tmp.n = n, tmp.m = M.m;
        for(int i = 0; i < n; i ++ )
            for(int k = 0; k < M.m; k ++ )
                for(int j = 0; j < m; j ++ )
                    tmp[i][j] = (tmp[i][j] + a[i][k] * M.a[k][j] % mod) % mod;
        return tmp;
    }

    void print()
    {
        for(int i = 0; i < n; i ++ )
        {
            for(int j = 0; j < m; j ++ )
                cout << a[i][j] << ' ';
            puts("");
        }
    }
}base, ans;

void get_next()
{
    for(int i = 2, j = 0; i <= m; i ++ )
    {
        while(j && s[i] != s[j + 1]) j = ne[j];
        if(s[i] == s[j + 1]) j ++;
        ne[i] = j;
    }
}

mat qmi(mat a, ll k)
{
    mat res;
    res.init();
    res.m = res.n = m;
    for(int i = 0; i < m; i ++ ) res[i][i] = 1;
    while(k)
    {
        if(k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), mod = read();
    scanf("%s", s + 1);

    get_next();

    for(int i = 0, j; i < m; i ++ )
        for(int u = '0'; u <= '9'; u ++ )
        {
            j = i;
            while(j && s[j + 1] != u) j = ne[j];
            if(s[j + 1] == u) j ++;
            base[i][j] ++;
        }

    base.n = base.m = m;
    // base.print();

    base = qmi(base, n);

    ll ret = 0;
    for(int i = 0; i < m; i ++ ) ret = (ret + base[0][i]) % mod;
    cout << ret << endl;
    
    return 0;
}
