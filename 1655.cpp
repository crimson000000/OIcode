#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
typedef vector<int> VI;

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

const int N = 200;
int n, m;
VI S[N][N];

VI add(VI a, VI b)
{
    VI c;
    int t = 0;
    for(int i = 0; i < a.size() || i < b.size(); i ++ )
    {
        if(i < a.size()) t += a[i];
        if(i < b.size()) t += b[i];

        c.push_back(t % 10);
        t /= 10;
    }
    if(t) c.push_back(1);
    return c;
}

VI mul(VI a, int b)
{
    VI c;
    int t = 0;
    for(int i = 0; i < a.size(); i ++ )
    {
        t += a[i] * b;
        c.push_back(t % 10);
        t /= 10;
    }
    while(t) c.push_back(t % 10), t /= 10;
    return c;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    for(int i = 1; i < N; i ++ ) S[i][1].push_back(1);
    for(int i = 2; i < N; i ++ )
        for(int j = 1; j <= i; j ++ )
            S[i][j] = add(S[i - 1][j - 1], mul(S[i - 1][j], j));

    while(cin >> n >> m)
    {
        if(n < m)
        {
            cout << 0 << endl;
            continue;
        }
        VI ans = S[n][m];
        for(int i = ans.size() - 1; i >= 0; i -- ) cout << ans[i];
        puts("");
    }
    
    return 0;
}
