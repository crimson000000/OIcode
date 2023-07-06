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

const int N = 5010;
int a[N];
unsigned int ans;
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= n; j ++ )
            for(int k = 1; k <= n; k ++ )
            {
                if(!(i ^ j) || !(i ^ k) || !(j ^ k)) continue; 
                ans += (a[i] / a[j]) * (a[j] / a[k]) * (a[i] / a[k]);
            }

    cout << ans << endl;
    
    return 0;
}
