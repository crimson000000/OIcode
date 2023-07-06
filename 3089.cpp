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

const int N = 2010;
ll f[N][N];
ll ans;
struct po
{
    int x, w;
    bool operator < (const po& a) const
    {
        return x < a.x;
    }
}q[N];
int n;

#define w(x) q[(x)].w
#define x(z) q[(z)].x

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        q[i].x = read();
        q[i].w = read();
        ans = max((ll)q[i].w, ans);
    }

    sort(q + 1, q + n + 1);

    for(int j = 1; j <= n; j ++ )   
    {
        f[j][j] = w(j);
        for(int i = j + 1, k = j + 1; i <= n; i ++ )
        {
            f[i][j] = f[i - 1][j] - w(i - 1);
            while(k > 1 && x(j) - x(k - 1) <= x(i) - x(j))
            {
                f[i][j] = max(f[i][j], f[j][-- k]);
            }
            f[i][j] += w(i);
            ans = max(ans, f[i][j]);
        }
    }

    for(int j = n; j; j -- )   
    {
        f[j][j] = w(j);
        for(int i = j - 1, k = j - 1; i; i -- )
        {
            f[i][j] = f[i + 1][j] - w(i + 1);
            while(k < n && x(k + 1) - x(j) <= x(j) - x(i))
            {
                f[i][j] = max(f[i][j], f[j][++ k]);
            }
            f[i][j] += w(i);
            ans = max(ans, f[i][j]);
        }
    }

    cout << ans << endl;

    return 0;
}