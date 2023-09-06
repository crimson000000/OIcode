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

const int N = 1e5 + 10, M = 110, P = 131, mod = 998244353;
bool f[20][N];
char s[N], t[M];
ll a[N];
int n, m, k = 1;
int len[N], op[N];
char tmp[N];
ll ppow[N];

inline ll HHash(char *s)
{
    int len = strlen(s + 1);
    ll res = 0;
    for(int i = 1; i <= len; i ++ )
        res = (res * P + s[i]) % mod;
    return res;
}

inline void pre()
{
    for(int i = 1; i <= n; i ++ )
    {
        if(s[i] == '?' || s[i] == '*')
        {
            if(i == 1) k --;
            a[k] = HHash(tmp);
            memset(tmp, 0, sizeof tmp);
            op[++ k] = ((s[i] == '?') ? 1 : 2);
        }
        else tmp[++ len[k]] = s[i];
    }
    a[k] = HHash(tmp);
    return;
}

struct Hash
{
    ll h[N];
    inline void init(char *s)
    {
        int n = strlen(s + 1);
        for(int i = 1; i <= n; i ++ )
            h[i] = (h[i - 1] * P + s[i]) % mod;
    }

    inline ll gethash(int l, int r)
    {
        return (h[r] - h[l - 1] * ppow[r - l + 1] % mod + mod) % mod;
    }
}h;

inline bool check(int x, int i)
{
    return a[x] == h.gethash(i - len[x] + 1, i);
}

bool sum[N];
inline void dp()
{
    f[0][0] = true;
    for(int i = 0; i <= m; i ++ ) sum[i] = true;
    for(int i = 1; i <= k; i ++ )
    {
        for(int j = 0; j <= m; j ++ ) f[i][j] = 0;
        for(int j = m; j >= len[i]; j -- )
        {
            // cout << "yeah" << endl;
            if(check(i, j))
            {
                if(op[i] == 0) f[i][j] = f[i - 1][j - len[i]];
                if(op[i] == 1) f[i][j] = f[i - 1][j - len[i] - 1];
                if(op[i] == 2) f[i][j] = sum[j - len[i]];
            }
        }
        sum[0] = 0;
        for(int j = 1; j <= m; j ++ ) sum[j] = sum[j - 1] | f[i][j];
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

    ppow[0] = 1;
    for(int i = 1; i < N - 5; i ++ ) ppow[i] = ppow[i - 1] * P % mod;

    pre();
    // cout << a[1] << endl;

    // for(int i = 1; i <= k; i ++ ) cout << len[i] << ' ';

    int T = read();
    while(T -- )
    {
        scanf("%s", t + 1);
        h.init(t);
        // cout << h.gethash(1, 3) << endl;
        // cout << check(1, 3) << endl;
        m = strlen(t + 1);

        dp();

        if(f[k][m]) puts("YES");
        else puts("NO");
    }

    return 0;
}