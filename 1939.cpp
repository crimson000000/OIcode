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

const int mod = 1e9 + 7;
int a[10][10], res[10][10];
ll k, T;

struct mat
{
    int m[5][5];
    int a, b;

    mat operator * (const mat& M) const
    {
        mat temp;
        memset(temp.m, 0, sizeof temp.m);
        temp.a = a, temp.b = M.b;
        for(int i = 1; i <= a; i ++ )
            for(int j = 1; j <= M.b; j ++ )
                for(int k = 1; k <= b; k ++ )
                    temp.m[i][j] = (temp.m[i][j] + (ll)m[i][k] * M.m[k][j] % mod) % mod;
        return temp;
    }
}init, ans, base;

mat qmi(mat a, ll k)
{
    mat res;
    memset(res.m, 0, sizeof res.m);
    res.m[1][1] = res.m[2][2] = res.m[3][3] = 1;
    res.a = res.b = 3;
    while(k)
    {
        if(k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> T;
    while(T -- )
    {
        cin >> k;
        
        base.m[1][3] = base.m[2][1] = base.m[3][2] = base.m[3][3] = 1;
        base.a = base.b = 3;

        init.a = 1;
        init.b = 3;
        init.m[1][1] = init.m[2][2] = init.m[3][3] = 1;

        if(k <= 3)
        {
            puts("1");
        }
        else
        {
            ans = init * qmi(base, k);
            cout << ans.m[1][3] << endl;
        }
    }
    
    return 0;
}
