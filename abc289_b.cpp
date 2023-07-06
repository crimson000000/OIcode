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
int a[N], way[N];
bool st[N];
bool mp[N];
int n, m;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();

    for(int i = 1; i <= m; i ++ )
    {
        a[i] = read();
        mp[a[i]] = true;
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(!mp[i])
        {
            for(int j = i; j > 0; j -- )
                if(!st[j])
                {
                    cout << j << " ";
                    st[j] = true;
                }
        }
    }
    
    return 0;
}
