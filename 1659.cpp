#define LOCAL
#include <bits/stdc++.h>
#define int long long
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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
const int N = 1e6 + 10;

int b[N];
char s[N << 1], t[N];
int f[N << 1];
int n, k, maxn, ans = 1;

void manacher(int len)
{
    s[0] = '|', s[1] = '#';
    for(int i = 1; i <= len; i ++ ) s[i << 1] = t[i], s[i << 1 | 1] = '#';
    len = len << 1 | 1, s[len + 1] = '!';
    int mid = 0, r = 1;
    for(int i = 1; i <= len; i ++ )
    {
        if(i > r) f[i] = 1;
        else f[i] = min(r - i, f[2 * mid - i]);
        while(s[i - f[i]] == s[i + f[i]]) f[i] ++;
        if(i + f[i] > r) r = i + f[i], mid = i;
        if((f[i] - 1) % 2) b[f[i] - 1] ++;
    }
}

const int mod = 19930726;
int qmi(int a, int k)
{
    int res = 1;
    while(k)
    {
        if(k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    n = read(), k = read();

    scanf("%s", t + 1);

    int len = n;
    manacher(len);

    ll sum = 0;
    for(int i = n; i > 0; i -- )
    {
        if(i % 2 == 0) continue;
        sum += b[i];
        if(k >= sum) 
        {
            ans = (ll)(ans * qmi(i, sum)) % mod;
            k -= sum;
        }
        else
        {
            ans = (ll)(ans * qmi(i, k)) % mod;
            k -= sum;
            break;
        }
    }

    if(k > 0) ans = -1;
    cout << ans << endl;
    
    return 0;
}
