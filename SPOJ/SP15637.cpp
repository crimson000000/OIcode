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

const int N = 35;
int k;
ll f[N][N][N][N][N];
int n[N], a[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    while(scanf("%d", &k), k)
    {
        memset(n, 0, sizeof n);
        for(int i = 1; i <= k; i ++ ) n[i] = read();
        memset(f, 0, sizeof f);
        
        f[0][0][0][0][0] = 1;

        for(a[1] = 0; a[1] <= n[1]; a[1] ++ )
            for(a[2] = 0; a[2] <= n[2]; a[2] ++ )
                for(a[3] = 0; a[3] <= n[3]; a[3] ++ )
                    for(a[4] = 0; a[4] <= n[4]; a[4] ++ )
                        for(a[5] = 0; a[5] <= n[5]; a[5] ++ )
                        {
                            ll &v = f[a[1]][a[2]][a[3]][a[4]][a[5]];
                            if(a[1] < n[1]) 
                                f[a[1] + 1][a[2]][a[3]][a[4]][a[5]] += v;
                            if(a[2] < a[1] && a[2] < n[2])
                                f[a[1]][a[2] + 1][a[3]][a[4]][a[5]] += v;
                            if(a[3] < a[2] && a[3] < n[3])
                                f[a[1]][a[2]][a[3] + 1][a[4]][a[5]] += v;
                            if(a[4] < a[3] && a[4] < n[4])
                                f[a[1]][a[2]][a[3]][a[4] + 1][a[5]] += v;
                            if(a[5] < a[4] && a[5] < n[5])
                                f[a[1]][a[2]][a[3]][a[4]][a[5] + 1] += v;
                        }

        cout << f[n[1]][n[2]][n[3]][n[4]][n[5]] << endl;
    }
    
    return 0;
}
