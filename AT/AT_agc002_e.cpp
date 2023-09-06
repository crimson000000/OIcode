#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;

inline ll read()
{
    ll x = 0, f = 1;
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
int a[N];
int n;
bool ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();

    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);

    for(int i = 1; i <= n; i ++ )
    {
        if(a[i + 1] < i + 1)
        {
            int j = 0;
            for(; a[j + i + 1] == i; j ++ );
            if((a[i] - i) & 1 || (j & 1)) puts("First");
            else puts("Second");
            return 0;
        }
    }
    
    return 0;
}
