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

const int N = 1e6 + 10;
int sum[N];
int n;

void init(int n)
{
    for(int i = 1; i <= n; i ++ )
        for(int j = i; j <= n; j += i)
            sum[j] ++;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n;
    init(n);
    int res = 0;
    for(int i = 1; i <= n; i ++ ) res += sum[i];

    cout << res << endl;
    
    return 0;
}
