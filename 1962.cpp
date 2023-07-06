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

ll k;
const int mod = 1e9 + 7;

struct mat
{
    int a, b;
    ll m[3][3];

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
}base, ans, init;

mat qmi(mat a, ll k)
{
    mat res;
    memset(res.m, 0, sizeof res.m);
    res.a = 2, res.b = 2;
    res.m[1][1] = res.m[2][2] = 1;
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

    cin >> k;

    base.m[1][2] = base.m[2][2] = base.m[2][1] = 1;
    base.a = base.b = 2;
    ans.m[1][1] = ans.m[1][2] = 1;
    ans.a = 1, ans.b = 2;
    
    ans = ans * qmi(base, k - 1);

    cout << ans.m[1][1] << endl;
    
    return 0;
}
