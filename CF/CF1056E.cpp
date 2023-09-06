#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
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

const int N = 1e6 + 10;
char t[N], s[N];
int n, m;
int first;
int cnt0, cnt1;
ll ans;

const int mod = 998244353, P1 = 131, P2 = 13331;
ull p1[N], h1[N];
ll p2[N], h2[N];

inline void init(int n)
{
    p1[0] = p2[0] = 1;
    for(int i = 1; i <= n; i ++ ) 
    {
        p1[i] = p1[i - 1] * P1;
        p2[i] = p2[i - 1] * P2 % mod;
    }
}

inline ull get1(int l, int r)
{
    return h1[r] - h1[l - 1] * p1[r - l + 1];
}

inline ll get2(int l, int r)
{
    return (h2[r] - h2[l - 1] * p2[r - l + 1] % mod + mod) % mod;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s%s", t + 1, s + 1);
    n = strlen(s + 1), m = strlen(t + 1);

    init(max(n, m));

    if(t[1] == '1')
    {
        for(int i = 1; i <= m; i ++ ) 
            if(t[i] == '1') t[i] = '0';
            else t[i] = '1';
    } 

    for(int i = 1; i <= n; i ++ ) 
    {
        h1[i] = h1[i - 1] * P1 + s[i];
        h2[i] = (h2[i - 1] * P2 + s[i]) % mod;
    }

    // cout << h1[2] << endl;

    for(int i = 1; i <= m; i ++ ) 
    {
        if(t[i] == '1')
        {
            cnt1 ++;
            if(!first) first = i;
        }
        else cnt0 ++;
    }

    // cout << first << endl;

    for(int x = 1; x <= n; x ++ )
    {
        int y = (n - (ll)cnt0 * x) / cnt1;
        if((ll)y * cnt1 != n - (ll)cnt0 * x) continue;
        if(y <= 0) break;
        // cout << x << ' ' << y << endl;
        // cout << (first - 1) * x + 1 << ' ' << (first - 1) * x + y << endl;
        ull h01 = get1(1, x), h11 = get1((first - 1) * x + 1, (first - 1) * x + y);
        ll h02 = get2(1, x), h12 = get2((first - 1) * x + 1, (first - 1) * x + y);
        // cout << h01 << ' ' << h11 << endl;
        
        if(h01 == h11 && h02 == h12) continue;
        
        ull H1 = 0;
        ll H2 = 0;
        for(int i = 1; i <= m; i ++ )
        {
            if(t[i] == '0')
            {
                H1 = H1 * p1[x] + h01;
                H2 = (H2 * p2[x] + h02) % mod;
            }
            else
            {
                H1 = H1 * p1[y] + h11;
                H2 = (H2 * p2[y] + h12) % mod;
            }
        }

        if(H1 == h1[n] && H2 == h2[n]) ans ++;
    }

    cout << ans << endl;

    return 0;
}