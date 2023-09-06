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

const int N = 2e6 + 10;
char s[N];
int bef[30], aft[30];
int z[N];
int n;

struct ta
{
    int c[30];
    #define lowbit(x) x & -x
    inline void add(int x, int v)
    {
        for(; x <= 28; x += lowbit(x)) c[x] += v;
    }

    inline int query(int x)
    {
        int res = 0;
        for(; x; x -= lowbit(x)) res += c[x];
        return res;
    }

    inline void clear()
    {
        memset(c, 0, sizeof c);
    }
}bit;

inline void getz(char *s, int n)
{
    z[1] = n;
    for(int i = 2, l = 1, r = 0; i <= n; i ++ )
    {
        if(i < r) z[i] = min(z[i - l + 1], r - i + 1);
        while(i + z[i] <= n && s[i + z[i]] == s[z[i] + 1]) z[i] ++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
}

inline void solve()
{
    memset(bef, 0, sizeof bef);
    memset(aft, 0, sizeof aft);
    memset(z, 0, sizeof z);
    bit.clear();

    scanf("%s", s + 1);
    n = strlen(s + 1);

    int all = 0, suf = 0, pre = 0;
    ll ans = 0;

    getz(s, n);

    for(int i = 1; i <= n; i ++ )
    {
        if(i + z[i] - 1 == n) z[i] --;
        // cout << z[i] << ' ';
    }

    // puts("");

    for(int i = 1; i <= n; i ++ )
        aft[s[i] - 'a'] ++;
    
    for(int i = 0; i < 26; i ++ )
        if(aft[i] & 1)
            all ++;
    // cout << all << endl;
    suf = all;
    for(int i = 1; i <= n; i ++ )
    {
        if(aft[s[i] - 'a'] & 1) suf --;
        else suf ++;
        aft[s[i] - 'a'] --;

        if(bef[s[i] - 'a'] & 1) pre --;
        else pre ++;
        bef[s[i] - 'a'] ++;

        if(i != 1 && i != n)
        {
            ll t = z[i + 1] / i + 1;
            // cout << z[i + 1] << ' ' << i << endl;
            ans += (t / 2) * bit.query(all + 1) + (t - t / 2) * bit.query(suf + 1);
        }

        bit.add(pre + 1, 1);
        // cout << pre << ' ' << suf << endl;
    }

    cout << ans << endl;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- ) solve();

    return 0;
}