#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
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

const int N = 64;
ull a[N];
ull p[N], ans;
int n;

void insert(ull x)
{
    for(int i = 63; i != -1; i -- )
    {
        if(!(x >> i) & 1) continue;
        if(!p[i])
        {
            p[i] = x;
            break;
        }
        else x ^= p[i];
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> n;
    for(int i = 1; i <= n; i ++ )
    {
        cin >> a[i];
        insert(a[i]);
    }

    for(int i = 63; i != -1; i -- )
        ans = max(ans, ans ^ p[i]);

    cout << ans << endl;
    
    return 0;
}
