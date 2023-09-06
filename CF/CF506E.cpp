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

const int N = 210, mod = 1e4 + 7;
char s[N];
int tmp[N];
int n, m, k;
ll ans;
int sz, Red, Green;

struct mat
{
    int a[N << 1][N << 1];
    mat() {memset(a, 0, sizeof a); }
    int * operator [] (int x)
    {
        return a[x];
    }

    mat operator * (const mat& b) const
    {
        mat tmp;
        for(int i = 1; i <= sz; i ++ )
            for(int k = i; k <= sz; k ++ )
            {
                for(int j = k; j <= sz; j ++ )
                    tmp[i][j] += (ll)a[i][k] * b.a[k][j] % mod;
                
                if(k % 20 == 0 || k == sz)
                    for(int j = k; j <= sz; j ++ )
                        tmp[i][j] %= mod;
            }
        return tmp;
    }
}G, PATH;

bool vis[N][N][N];
int f[N][N][N];
inline int getpath1(int l, int r, int num)
{
    if(num < 0) return 0;
    if(l > r) return num ? 0 : 1;
    if(vis[l][r][num]) return f[l][r][num];
    vis[l][r][num] = true;
    if(s[l] != s[r]) f[l][r][num] = getpath1(l + 1, r, num - 1) + getpath1(l, r - 1, num - 1);
    else f[l][r][num] = getpath1(l + 1, r - 1, num);
    return f[l][r][num] % mod;
}

inline int getpath2(int l, int r, int num)
{
    if(num < 0) return 0;
    if(l >= r) return 0;
    if(l == r - 1 && s[l] == s[r]) return num ? 0 : 1;
    if(vis[l][r][num]) return f[l][r][num];
    vis[l][r][num] = true;
    if(s[l] != s[r]) f[l][r][num] = getpath2(l + 1, r, num - 1) + getpath2(l, r - 1, num - 1);
    else f[l][r][num] = getpath2(l + 1, r - 1, num);
    return f[l][r][num] % mod;
}

inline mat qmi(mat a, int k)
{
    mat res = a;
    k --;
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

    scanf("%s", s + 1);
    n = read();
    m = strlen(s + 1);

    k = m + n >> 1;

    for(int i = 0; i < m; i ++ ) 
    {
        tmp[i] = getpath1(1, m, i);
        // cout << tmp[i] << endl;
    }
    Red = m - 1, Green = m + 1 >> 1, sz = Red + Green * 2;

    for(int i = 1; i < Red + Green; i ++ ) G[i][i + 1] = 1;
    for(int i = Red + 1; i <= Red + Green; i ++ )
        G[i][i + Green] = 1;
    
    for(int i = 1; i <= Red; i ++ ) G[i][i] = 24;
    for(int i = Red + 1; i <= Red + Green; i ++ ) G[i][i] = 25;
    for(int i = Red + Green + 1; i <= sz; i ++ ) G[i][i] = 26;
    PATH = qmi(G, k);
    // for(int i = 1; i <= sz; i ++ )
    // {
    //     for(int j = 1; j <= sz; j ++ )
    //         cout << G[i][j] << ' ';
    //     puts("");
    // }
    if((m + n) & 1)
    {
        memset(vis, 0, sizeof vis);
        memset(f, 0, sizeof f);
        for(int i = 0; i <= m - 2; i ++ )
        {
            int cnt = getpath2(1, m, i);
            if(m - i & 1) continue;
            ans = (ans - cnt * PATH[Red + 1 - i][Red + (m - i >> 1)]) % mod;
        }
        ans += mod;
        PATH = PATH * G;
    }

    for(int i = 0; i < m; i ++ )
    {
        int goal = m - i + 1 >> 1;
        ans = (ans + tmp[i] * PATH[Red + 1 - i][Red + Green + goal]) % mod;
    }

    cout << ans << endl;

    return 0;
}
