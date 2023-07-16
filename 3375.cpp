#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> PII;

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

const int N = 1e7 + 10;
int ne[N];
char s[N], t[N];
int n, m;

signed main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s%s", s + 1, t + 1);
    n = strlen(s + 1), m = strlen(t + 1);

    ne[1] = 0;
    for(int i = 2, j = 0; i <= m; i ++ )
    {
        while(j && t[i] != t[j + 1]) j = ne[j];
        if(t[i] == t[j + 1]) j ++;
        ne[i] = j;
    }

    for(int i = 1, j = 0; i <= n; i ++ )
    {
        while(j && s[i] != t[j + 1]) j = ne[j];
        if(s[i] == t[j + 1]) j ++;
        if(j == m)
        {
            printf("%d\n", i - m + 1);
        }
    }

    for(int i = 1; i <= m; i ++ ) printf("%d ", ne[i]);

    return 0;
}
