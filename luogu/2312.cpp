#define LOCAL
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> PII;

const int N = 110, mod = 998244353;

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
        x = ((x << 3) + (x << 1) + ch - '0') % mod;
        ch = getchar();
    }
    return x * f;
}

int n, m;
ll a[N];
vector<int> ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 0; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= m; i ++ )
    {
        ll res = a[n];
        for(int j = n; j >= 0; j -- )
            res = (res * i + a[j - 1]) % mod;
        if(!res) ans.push_back(i);
    }

    printf("%d\n", ans.size());
    for(auto res : ans)
        printf("%d\n", res);

    return 0;
}