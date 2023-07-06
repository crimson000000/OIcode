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

const int N = 1e6 + 10;
char s[N], t[N], ans[N], rest[N];
int cnt[5];
int ne[N];
int n, m, tt;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);

    for(int i = 1; i <= n; i ++ ) cnt[s[i] - '0'] ++;
    for(int i = 2, j = 0; i <= m; i ++ )
    {
        while(j && t[j + 1] != t[i]) j = ne[j];
        if(t[i] == t[j + 1]) j ++;
        ne[i] = j;
    }

    for(int i = 1; i <= m; i ++ )
        if(cnt[t[i] - '0'])
        {
            ans[++ tt] = t[i];
            cnt[t[i] - '0'] --;
            if(!cnt[0] && !cnt[1]) break;
        }

    int len = 0;
    for(int i = ne[m] + 1; i <= m; i ++ ) 
        rest[++ len] = t[i];

    while(1)
    {
        bool flag = false;
        for(int i = 1; i <= len; i ++ )
        {
            if(!cnt[rest[i] - '0'])
            {
                flag = true;
                break;
            }
            ans[++ tt] = rest[i];
            cnt[rest[i] - '0'] --;
        }
        if(flag) break;
    }

    while(cnt[0]) ans[++ tt] = '0', cnt[0] --;
    while(cnt[1]) ans[++ tt] = '1', cnt[1] --;

    for(int i = 1; i <= tt; i ++ ) cout << ans[i];

    return 0;
}