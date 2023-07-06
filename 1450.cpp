#define LOCAL
#include <bits/stdc++.h>
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

const int N = 1e5 + 10;
ll f[N];
int c[6], d[6], n, s;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    for(int i = 1; i <= 4; i ++ ) cin >> c[i];
    cin >> n;

    f[0] = 1;
    for(int i = 1; i <= 4; i ++ )
        for(int j = 0; j <= 100000; j ++ )
            if(j >= c[i]) f[j] += f[j - c[i]];

    while(n -- )
    {
        for(int i = 1; i <= 4; i ++ ) cin >> d[i];
        cin >> s;

        ll ans = 0;
        for(int i = 0; i < 16; i ++ )
        {
            int cnt = 0;
            ll t = s;
            for(int k = 1; k <= 4; k ++ )
                if(i >> (k - 1) & 1)
                {
                    cnt ^= 1;
                    t -= c[k] * (d[k] + 1);
                }
            if(t < 0) continue;
            if(!cnt) ans += f[t];
            else ans -= f[t];
        }
        cout << ans << endl;
    }
    
    return 0;
}
