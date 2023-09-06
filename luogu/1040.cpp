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

const int N = 110;
ll f[N][N];
int root[N][N];
ll a[N];
int n;

void print(int l, int r)
{
    if(l > r) return;
    cout << root[l][r] << " ";
    if(l == r) return;
    print(l, root[l][r] - 1);
    print(root[l][r] + 1, r);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n;

    for(int i = 1; i <= n; i ++ ) 
    {
        cin >> a[i];
        root[i][i] = i;
        f[i][i] = a[i];
    }
    
    for(int len = 2; len <= n; len ++ )
    {
        for(int l = 1; l <= n; l ++ )
        {
            int r = l + len - 1;
            if(r > n) break;

            f[l][r] = f[l + 1][r] + f[l][l];
            root[l][r] = l;
            for(int k = l + 1; k < r; k ++ )
            {
                if(f[l][k - 1] * f[k + 1][r] + a[k] > f[l][r])
                {
                    f[l][r] = f[l][k - 1] * f[k + 1][r] + a[k];
                    root[l][r] = k;
                }
            }
        }
    }

    cout << f[1][n] << endl;
    print(1, n);
    
    return 0;
}
