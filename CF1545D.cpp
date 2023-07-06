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

const int N = 1010;
ll f[N], s[N];
ll x[N][N];
ll n, k;
unordered_map<ll, int> mp;
int flag, flag1;
ll standard, delta;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    for(int i = 1; i <= k; i ++ )
        for(int j = 1; j <= n; j ++ )
        {
            x[i][j] = read();
            f[i] += x[i][j];
            s[i] += x[i][j] * x[i][j];
        }

    for(int i = 2; i <= k; i ++ ) mp[f[i] - f[i - 1]] ++;

    for(int i = 2; i <= k; i ++ )
    {
        if(mp[f[i] - f[i - 1]] == 1)
        {
            flag = i;
            if(i <= 3) flag1 = 5;
            else flag1 = 2;
            break;
        }
    }

    cout << flag - 1 << ' ';

    delta = f[flag1] - f[flag1 - 1] - f[flag] + f[flag - 1];
    standard = s[flag1 + 1] + s[flag1 - 1] - 2 * s[flag1];

    ll ans;
    for(int i = 1; i <= n; i ++ )
    {
        int nowx = x[flag][i];
        if(s[flag + 1] + s[flag - 1] - 2 * (s[flag] - nowx * nowx + (nowx + delta) * (nowx + delta)) == standard)
        {
            ans = nowx + delta;
            cout << ans << endl;
            cout.flush();
            return 0;
        }
    }

    return 0;
}