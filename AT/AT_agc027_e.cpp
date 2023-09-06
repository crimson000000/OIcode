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

const int N = 1e6 + 10, mod = 1e9 + 7;;
ll f[N];
int nxt[N][3];
char s[N];
int a[N], sum[N];
int n;
ll ans;
bool same;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);

    for(int i = 1; i <= n; i ++ )
    {
        if(s[i] == s[i - 1]) same = true;
        a[i] = s[i] - 'a' + 1;
        sum[i] = (sum[i - 1] + a[i]) % 3;
        // cout << sum[i] << ' ';
    }

    if(!same)
    {
        puts("1");
        return 0;
    }

    if(a[n] == 1)
    {
        nxt[n][0] = n + 1;
        nxt[n][1] = n;
        nxt[n][2] = n + 1;
    }
    else
    {
        nxt[n][0] = n + 1;
        nxt[n][1] = n + 1;
        nxt[n][2] = n;
    }

    for(int i = n - 1; i >= 1; i -- )
    {
        if(a[i] == 1)
        {
            nxt[i][0] = nxt[i + 1][2];
            nxt[i][1] = i;
            nxt[i][2] = nxt[i + 1][1];
        }
        else
        {
            nxt[i][0] = nxt[i + 1][1];
            nxt[i][1] = nxt[i + 1][2];
            nxt[i][2] = i;
        }
    }

    f[0] = 1;
    for(int i = 0; i <= n; i ++ )
    {
        f[nxt[i + 1][1]] = (f[nxt[i + 1][1]] + f[i]) % mod;
        f[nxt[i + 1][2]] = (f[nxt[i + 1][2]] + f[i]) % mod;
        if((sum[n] - sum[i] + 3) % 3 == 0 && i)
            ans = (ans + f[i]) % mod; 
    }

    printf("%lld\n", ans);

    return 0;
}