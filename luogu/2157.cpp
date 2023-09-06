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

const int N = 1010, M = 1 << 9;
int t[N], b[N];
int f[N][M][20], tw[N];
int n;

int TT(int x, int y)
{
    if(x == 0) return 0;
    else return t[x] ^ t[y];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    for(int i = 0; i <= 20; i ++ ) tw[i] = 1 << i;

    while(T -- )
    {
        n = read();
        for(int i = 1; i <= n; i ++ ) 
        {
            t[i] = read();
            b[i] = read();
        }

        memset(f, 0x3f, sizeof f);
        f[1][0][7] = 0;
        for(int i = 1; i <= n; i ++ )
            for(int st = 0; st < 1 << 8; st ++ )
                for(int k = -8; k < 8; k ++ )
                {
                    if(f[i][st][k + 8] == 0x3f3f3f3f) continue;
                    if(st & 1)
                       f[i + 1][st >> 1][k - 1 + 8] = min(f[i + 1][st >> 1][k - 1 + 8], f[i][st][k + 8]);
                    else
                    {
                        int rx = 0x3f3f3f3f;
                        for(int lx = 0; lx <= 7; lx ++ )
                        {
                            if(st & tw[lx]) continue;
                            if(i + lx > rx) break;
                            
                            rx = min(rx, i + lx + b[i + lx]);
                            f[i][st | tw[lx]][lx + 8] = min(f[i][st | tw[lx]][lx + 8], f[i][st][k + 8] + TT(i + k, i + lx));
                        }
                    }
                }

        int res = 0x3f3f3f3f;
        for(int k = -8; k < 1; k ++ )
            res = min(res, f[n][1][k + 8]);

        cout << res << endl;
    }
    
    return 0;
}
