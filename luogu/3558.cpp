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

const int N = 1e6 + 10, INF = 0x3f3f3f3f;
int f[N][3];
int a[N];
int n;

inline int gettime(int last, int from, int to)
{
    if(last == 0)
    {
        if(from == to) return 0;
        else return INF;
    }
    if(last == 1)
    {
        if(from <= to) return to - from;
        else return INF;
    }
    else
    {
        if(from >= to) return from - to;
        else return INF;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    memset(f, 0x3f, sizeof f);
    memset(f[0], 0, sizeof f[0]);
    f[1][a[1] + 1] = 0;
    for(int i = 2; i <= n; i ++ )
    {
        int t = a[i];
        f[i][0] = min(f[i][0], f[i - 1][0] + gettime(-1, t, -1)); 
        f[i][1] = min(f[i][1], f[i - 1][1] + gettime(0, t, 0));
        f[i][1] = min(f[i][1], f[i - 1][0] + gettime(-1, t, 0));
        f[i][2] = min(f[i][2], f[i - 1][0] + gettime(-1, t, 1));
        f[i][2] = min(f[i][2], f[i - 1][1] + gettime(0, t, 1));
        f[i][2] = min(f[i][2], f[i - 1][2] + gettime(1, t, 1));
    }

    ll res = min(f[n][0], min(f[n][1], f[n][2]));
    if(res >= INF / 2) puts("BRAK");
    else cout << res << endl;
    
    return 0;
}
