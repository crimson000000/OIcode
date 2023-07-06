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

const int mod = 1000003, N = 55, M = 1 << 15;
char s[N][60];
int match[N][N];
int f[N][M];
int n, m, len;
int ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();

    while(T -- )
    {
        memset(f, 0, sizeof f);
        memset(match, 0, sizeof match);
        ans = 0;
        n = read(), m = read();
        for(int i = 0; i < n; i ++ ) scanf("%s", s[i]);

        len = strlen(s[0]);

        for(int i = 0; i < len; i ++ )
            for(int j = 0; j < 26; j ++ )
                for(int k = 0; k < n; k ++ )
                    if(s[k][i] == '?' || s[k][i] == j + 'a')
                        match[i][j] |= 1 << k;

        f[0][(1 << n) - 1] = 1;
        for(int i = 0; i < len; i ++ )
            for(int j = 0; j < 1 << n; j ++ )
                if(f[i][j])
                    for(int k = 0; k < 26; k ++ )
                        f[i + 1][match[i][k] & j] = (f[i][j] + f[i + 1][match[i][k] & j]) % mod;

        for(int i = 0; i < 1 << n; i ++ )
        {
            int cnt = 0;
            for(int j = 0; j < n; j ++ )
                if(i >> j & 1) cnt ++;
            if(cnt == m) 
            {
                ans = (ans + f[len][i]) % mod;
            }
        }

        cout << ans << endl;
        puts("");
    }
    
    return 0;
}
