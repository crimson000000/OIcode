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

const int N = 1010;
int n, m, x, y;
double a[N][N], f[N][N], b[N];

void work(int m) {
	for (int i = 1; i <= m; i ++) {
		double w = 1.0 / a[i][i];
		a[i][i] *= w;
		b[i] *= w;
		if (i == m) break; 
		a[i][i + 1] *= w;
		w = a[i + 1][i] / a[i][i];
		a[i + 1][i] -= w * a[i][i];
		a[i + 1][i + 1] -= w * a[i][i + 1];
		b[i + 1] -= w * b[i];
	}
	for (int i = m - 1; i; i --)
		b[i] -= b[i + 1] * a[i][i + 1];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), x = read(), y = read();
    if(n > 1 && x != n)
    {
        for(int i = n - 1; i >= x; i -- )
        {
            for(int j = 1; j <= m; j ++ )
            {
                // cout << "yeah" << endl;
                if(j == 1)
                {
                    a[j][1] = 2.0 / 3, a[j][2] = -1.0 / 3, b[j] = 1.0 / 3 * f[i + 1][j] + 1;
                }
                else if(j == m)
                {
                    a[j][m] = 2.0 / 3, a[j][m - 1] = -1.0 / 3, b[j] = 1.0 / 3 * f[i + 1][m] + 1;
                }
                else
                {
                    a[j][j] = 3.0 / 4, a[j][j - 1] = -1.0 / 4, a[j][j + 1] = -1.0 / 4, b[j] = 1.0 / 4 * f[i + 1][j] + 1;
                }
            }
            if(m == 1) 
            {
                a[1][1] = 1 / 2.0;
                b[m] = f[i + 1][m] / 2.0 + 1;
            }
            work(m);
            for(int j = 1; j <= m; j ++ )
                f[i][j] = b[j];
        }
        printf("%.4lf\n", f[x][y]);
    }
    else
    {
        puts("0.000000000");
    }
    
    return 0;
}
