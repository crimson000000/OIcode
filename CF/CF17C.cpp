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

const int N = 160, mod = 51123987;
int f[N][N / 3][N / 3][N / 3];
int ne[N][3];
char s[N];
int n, ans;

inline int abs(int x)
{
    return x < 0 ? -x : x;
}

inline int add(int a, int b)
{
    int res = a + b;
    while(res >= mod) res -= mod;
    return res;
}

inline bool vaild(int a, int b, int c)
{
    return a + b + c == n && abs(a - b) <= 1 && abs(b - c) <= 1 && abs(c - a) <= 1;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    scanf("%s", s + 1);

    ne[n + 1][0] = ne[n + 1][1] = ne[n + 1][2] = n + 1;
    for(int i = n; i; i -- )
    {
        ne[i][0] = ne[i + 1][0];
        ne[i][1] = ne[i + 1][1];
        ne[i][2] = ne[i + 1][2];
        if(s[i] == 'a') ne[i][0] = i;
        if(s[i] == 'b') ne[i][1] = i;
        if(s[i] == 'c') ne[i][2] = i;
    }

    f[1][0][0][0] = 1;
    int lim = (n + 2) / 3;
    for(int i = 1; i <= n; i ++ )
        for(int a = 0; a <= lim; a ++ )
            for(int b = 0; b <= lim; b ++ )
                for(int c = 0; c <= lim; c ++ )
                {
                    if(vaild(a, b, c))
                        ans = add(ans, f[i][a][b][c]);
                    f[ne[i][0]][a + 1][b][c] = add(f[ne[i][0]][a + 1][b][c], f[i][a][b][c]);
                    f[ne[i][1]][a][b + 1][c] = add(f[ne[i][1]][a][b + 1][c], f[i][a][b][c]);
                    f[ne[i][2]][a][b][c + 1] = add(f[ne[i][2]][a][b][c + 1], f[i][a][b][c]);
                }

    // for(int i = 1; i <= n; i ++ )
    //     for(int a = 0; a <= lim; a ++ )
    //         for(int b = 0; b <= lim; b ++ )
    //             for(int c = 0; c <= lim; c ++ )
    //             {
    //                 printf("f[%d, %d, %d, %d] %d\n", i, a, b, c, f[i][a][b][c]);
    //             } 

    cout << ans << endl;

    return 0;
}
