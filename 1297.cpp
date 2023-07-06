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

const int N = 1e7 + 10;
int a[N];
int n, A, B, C;
double ans;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%d%d%d%d%d", &n, &A, &B, &C, &a[1]);
    for (int i = 2; i <= n; i++)
        a[i] = ((long long) a[i - 1] * A + B) % 100000001;
    for (int i = 1; i <= n; i++)
        a[i] = a[i] % C + 1;

    ans = 1.0 / max(a[1], a[n]);
    for(int i = 2; i <= n; i ++ )
        ans += 1.0 / max(a[i - 1], a[i]);

    printf("%.3lf\n", ans);
    
    return 0;
}
