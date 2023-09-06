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
bitset<N> a[N];
char s[N];
int n, m, ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    for(int i = 1; i <= m; i ++ )
    {
        scanf("%s", s + 1);
        for(int j = 1; j <= n; j ++ )
            if(s[j] == '1')
                a[i][j] = true;
        int x = read();
        a[i][n + 1] = x;
    }

    for(int i = 1; i <= n; i ++ )
    {
        int pos = i;
        for(int j = i; j <= m; j ++ )
            if(a[j][i])
            {
                pos = j;
                break;
            }
        
        swap(a[i], a[pos]);
        
        if(!a[i][i])
        {
            puts("Cannot Determine");
            return 0;
        }
    
        ans = max(ans, pos);
        for(int j = 1; j <= m; j ++ )
        {
            if(j == i || !a[j][i]) continue;
            a[j] ^= a[i];
        }
    }

    cout << ans << endl;
    for(int i = 1; i <= n; i ++ )
    {
        if(!a[i][n + 1]) puts("Earth");
        else puts("?y7M#");
    }
    
    return 0;
}
