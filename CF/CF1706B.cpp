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

const int N = 1e6 + 10;
int lst[N], cnt[N];
int n;
int a[N];

inline void solve()
{
    for(int i = 1; i <= n; i ++ ) lst[i] = cnt[i] = 0;
    n = read(); 
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= n; i ++ )
    {
        cnt[a[i]] ++;
        if(lst[a[i]] && (i - lst[a[i]] + 1) & 1) cnt[a[i]] --;
        lst[a[i]] = i;
    }

    for(int i = 1; i <= n; i ++ )
        printf("%d ", cnt[i]);
    puts("");
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