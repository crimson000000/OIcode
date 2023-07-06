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

int p, q, n, mod;
struct mat
{
    int a, b;
    ll m[5][5];

    mat operator * (const mat& M) const 
    {
        mat temp;
        temp.a = a, temp.b = M.b;
        memset(temp.m, 0, sizeof temp.m);
        for(int i = 1; i <= a; i ++ )
            for(int j = 1; j <= M.b; j ++ )
                for(int k = 1; k <= b; k ++ )
                    temp.m[i][j] = (temp.m[i][j] + m[i][k] * M.m[k][j] % mod) % mod;
        return temp;
    }
}base, ans;

mat qmi(mat a, int k)
{
    mat temp;
    temp.a = a.a, temp.b = a.b;
    memset(temp.m, 0, sizeof temp.m);
    for(int i = 1; i <= 2; i ++ ) temp.m[i][i] = 1;

    while(k)
    {
        if(k & 1) temp = temp * a;
        a = a * a;
        k >>= 1;
    }
    return temp;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> p >> q >> ans.m[1][1] >> ans.m[1][2] >> n >> mod;

    base.m[1][2] = q;
    base.m[2][1] = 1;
    base.m[2][2] = p;
    ans.a = 1, ans.b = 2;
    base.a = base.b = 2;

    ans = ans * qmi(base, n - 1);

    cout << ans.m[1][1] << endl;
    
    return 0;
}
