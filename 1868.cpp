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

const int N = 3e6 + 10;
int n, maxr;
int f[N], g[N];
vector<int> range[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();

    for(int i = 1; i <= n; i ++ )
    {
        int l = read(), r = read();
        maxr = max(r, maxr);
        range[r].push_back(l - 1);
    }

    for(int i = 1; i <= maxr; i ++ )
    {
        f[i] = max(f[i], f[i - 1]);
        for(int j = 0; j < range[i].size(); j ++ )
            f[i] = max(f[i], f[range[i][j]] + i - range[i][j]);
    }

    cout << f[maxr] << endl;
    
    return 0;
}
