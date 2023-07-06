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

const int N = 18, S = 1 << 17;
int d[N][N];
int f[N][S];
int n;
struct point
{
    int x, y, z;
}q[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 0; i < n; i ++ )
        q[i].x = read(), q[i].y = read(), q[i].z = read();

    for(int i = 0; i < n; i ++ )
        for(int j = 0; j < n; j ++ )
        {
            d[i][j] = abs(q[i].x - q[j].x) + abs(q[i].y - q[j].y) + max(0, q[j].z - q[i].z);
        }

    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    f[0][1] = 0;
    
    for(int i = 0; i < (1 << n); i ++ )
        for(int j = 0; j < n; j ++ )
            if(i >> j & 1)
                for(int k = 0; k < n; k ++ )
                    if(!(i >> k & 1))
                        f[k][i | (1 << k)] = min(f[k][i | (1 << k)], f[j][i] + d[j][k]);
    
    int ans = 0x3f3f3f3f;
    for(int i = 1; i < n; i ++ ) 
        ans = min(ans, f[i][(1 << n) - 1] + d[i][0]);
    
    cout << ans << endl;

    return 0;
}