/*#define LOCAL
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

const int N = 510, M1 = 20080113, M2 = 20070912, P = 13331, mod = 998244353;
char a[N][N];
int Hash[N][N];
int t[N], s[26][N << 2];
bitset<(N >> 1)> ok;
int f[N << 2], p[N]; 
int cnt[N][N][26], idx;
ll ans;
int n, m, len;
int tt;

// inline int gethash(int k, int l, int r)
// {
//     int cntt = 0;
//     int res = 0;
//     int cnt0, cnt1, cnt2, cnt3, cnt4, cnt5, cnt6, cnt7, cnt8, cnt9, cnt10, cnt11, cnt12, cnt13, cnt14, cnt15, cnt16, cnt17, cnt18, cnt19, cnt20, cnt21, cnt22, cnt23, cnt24, cnt25;
//     l = l - 1;
//     tt += 26;
//     cnt0 = cnt[k][r][0] - cnt[k][l][0];
//     if(cnt0 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt0) % mod;
//     cnt1 = cnt[k][r][1] - cnt[k][l][1];
//     if(cnt1 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt1) % mod;
//     cnt2 = cnt[k][r][2] - cnt[k][l][2];
//     if(cnt2 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt2) % mod;
//     cnt3 = cnt[k][r][3] - cnt[k][l][3];
//     if(cnt3 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt3) % mod;
//     cnt4 = cnt[k][r][4] - cnt[k][l][4];
//     if(cnt4 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt4) % mod;
//     cnt5 = cnt[k][r][5] - cnt[k][l][5];
//     if(cnt5 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt5) % mod;
//     cnt6 = cnt[k][r][6] - cnt[k][l][6];
//     if(cnt6 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt6) % mod;
//     cnt7 = cnt[k][r][7] - cnt[k][l][7];
//     if(cnt7 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt7) % mod;
//     cnt8 = cnt[k][r][8] - cnt[k][l][8];
//     if(cnt8 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt8) % mod;
//     cnt9 = cnt[k][r][9] - cnt[k][l][9];
//     if(cnt9 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt9) % mod;
//     cnt10 = cnt[k][r][10] - cnt[k][l][10];
//     if(cnt10 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt10) % mod;
//     cnt11 = cnt[k][r][11] - cnt[k][l][11];
//     if(cnt11 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt11) % mod;
//     cnt12 = cnt[k][r][12] - cnt[k][l][12];
//     if(cnt12 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt12) % mod;
//     cnt13 = cnt[k][r][13] - cnt[k][l][13];
//     if(cnt13 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt13) % mod;
//     cnt14 = cnt[k][r][14] - cnt[k][l][14];
//     if(cnt14 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt14) % mod;
//     cnt15 = cnt[k][r][15] - cnt[k][l][15];
//     if(cnt15 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt15) % mod;
//     cnt16 = cnt[k][r][16] - cnt[k][l][16];
//     if(cnt16 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt16) % mod;
//     cnt17 = cnt[k][r][17] - cnt[k][l][17];
//     if(cnt17 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt17) % mod;
//     cnt18 = cnt[k][r][18] - cnt[k][l][18];
//     if(cnt18 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt18) % mod;
//     cnt19 = cnt[k][r][19] - cnt[k][l][19];
//     if(cnt19 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt19) % mod;
//     cnt20 = cnt[k][r][20] - cnt[k][l][20];
//     if(cnt20 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt20) % mod;
//     cnt21 = cnt[k][r][21] - cnt[k][l][21];
//     if(cnt21 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt21) % mod;
//     cnt22 = cnt[k][r][22] - cnt[k][l][22];
//     if(cnt22 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt22) % mod;
//     cnt23 = cnt[k][r][23] - cnt[k][l][23];
//     if(cnt23 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt23) % mod;
//     cnt24 = cnt[k][r][24] - cnt[k][l][24];
//     if(cnt24 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt24) % mod;
//     cnt25 = cnt[k][r][25] - cnt[k][l][25];
//     if(cnt25 & 1) cntt ++;
//     res = ((ll)res * P % mod + cnt25) % mod;
    
//     if(cntt <= 1) ok[k] = true;
//     return res;
// }

inline bool cmp(int a, int b)
{
    if(!ok[a] || !ok[b]) return 0;
    for(int i = 0; i < 26; i ++ )
        if(s[a][i] != s[b][i])
            return 0;
    return true;
}

inline int manacher(int len)
{
    int mid = 0, r = 0;
    for(register int i = 1; i <= len; i ++ )
    {
        if(!ok[i]) continue;
        if(i <= r) f[i] = min(f[2 * mid - i], r - i + 1);
        while(cmp(i + f[i], i - f[i]) && i - f[i] >= 1 && i + f[i] <= len) 
            f[i] ++;
        if(i + f[i] > r) r = i + f[i] - 1, mid = i;
    }
    int ans = 0;
    for(int i = 1; i <= len; i ++ ) ans += f[i] >> 1;
    // for(int i = 0; i <= len + 1; i ++ ) cout << f[i] << ' ';
    // puts("");
    return ans;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    double st = clock();
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for(register int i = 1; i <= n; i ++ ) cin >> (a[i] + 1);
    for(register int i = 1; i <= n; i ++ )
        for(register int j = 1; j <= m; j ++ )
        {
            for(register int k = 0; k < 26; k ++ )
                cnt[i][j][k] = cnt[i][j - 1][k];
            cnt[i][j][a[i][j] - 'a'] ++;
        }
    
    for(register int L = 1; L <= m; L ++ )
    {
        for(register int R = L; R <= m; R ++ )
        {
            idx = -5;
            ok.reset();
            for(register int k = 1; k <= n; k ++ )
            {
                int cntttt = 0;
                for(int u = 0; u < 26; u ++ )
                {
                    int t = cnt[k][R][u] - cnt[k][L - 1][u];
                    s[k * 2 - 1][u] = t;
                    if(t & 1) cntttt ++;
                }
                if(cntttt < 2) ok[k * 2 - 1] = true;
            }
            memset(f, 0, sizeof f);
            ans += manacher(n * 2);
        }
    }

    cout << ans << endl;
    // cout << (clock() - st) / CLOCKS_PER_SEC << endl;

    return 0;
}
*/

#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

inline int read()
{
    int x = 0, f = 1;
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

const int N = 510, M1 = 20080113, M2 = 20070912, P = 13331, mod = 998244353;
char a[N][N];
ll Hash[N][N];
ll t[N], s[N << 2];
bool ok[N];
int f[N << 2];
ll p[N]; 
int cnt[N][N][26], idx;
ll ans;
int n, m, len;
inline int add(int x,int y)
{
    if(x+y>mod) return x+y-mod;
    return x+y;
}
inline ll gethash(int k, int l, int r)
{
    int cntt = 0;
    ll res = 0;
    for(register int i = 0; i < 26; i ++ )
    {
        int cnti = cnt[k][r][i] - cnt[k][l - 1][i];
        if(cnti & 1) cntt ++;
        res = add(res * P%mod,cnti);
    }
    if(cntt <= 1) ok[k] = true;
    return res;
}

inline void init()
{
    len = 0;
    s[++ len] = M1;
    for(register int i = 1; i <= n; i ++ )
    {
        if(ok[i])
            s[++ len] = t[i];
        else s[++ len] = idx --;
        s[++ len] = M1;
    }
}

inline int manacher(int len)
{
    for(int i=0;i<=len;i++) f[i]=0;
    int mid = 0, r = 0;
    for(register int i = 1; i <= len; i ++ )
    {
        if(s[i] < 0) continue;
        if(i <= r) f[i] = min(f[2 * mid - i], r - i + 1);
        while(s[i + f[i]] == s[i - f[i]] && i - f[i] >= 1 && i + f[i] <= len) 
            f[i] ++;
        if(i + f[i] > r) r = i + f[i] - 1, mid = i;
    }
    int ans = 0;
    for(int i = 1; i <= len; i ++ ) ans += f[i] / 2;
    return ans;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    double st = clock();

    n = read(), m = read();
    for(register int i = 1; i <= n; i ++ ) scanf("%s", a[i] + 1);
    p[0] = 1;
    for(register int i = 1; i < N - 5; i ++ ) p[i] = p[i - 1] * P % mod;

    for(register int i = 1; i <= n; i ++ )
        for(register int j = 1; j <= m; j ++ )
        {
            for(register int k = 0; k < 26; k ++ )
                cnt[i][j][k] = cnt[i][j - 1][k];
            cnt[i][j][a[i][j] - 'a'] ++;
        }
    
    for(register int L = 1; L <= m; L ++ )
    {
        for(register int R = L; R <= m; R ++ )
        {
            idx = -5;
            for(int k=1;k<=n;k++) ok[k]=false;
            for(register int k = 1; k <= n; k ++ )
                t[k] = gethash(k, L, R);
            init();
            ans += manacher(len);
        }
    }

    cout << ans << endl;
    // cout << (clock() - st) / CLOCKS_PER_SEC << endl;

    return 0;
}