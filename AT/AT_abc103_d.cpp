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
struct seg
{
    int l, r;
    bool operator < (const seg& a) const
    {
        return r < a.r;
    }
}a[N];
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ ) 
    {
        int x = read(), y = read();
        a[i] = {x, y};
    }

    sort(a + 1, a + m + 1);

    int ans = 0, maxn = 1;
    for(int i = 1; i <= m; i ++ )
    {
        if(a[i].l >= maxn)
        {
            
            maxn = a[i].r;
            ans ++;
        }
    }

    cout << ans << endl;

    return 0;
}