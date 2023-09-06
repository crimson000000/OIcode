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
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10;
struct item
{
    int num, c;
    bool operator < (const item& a) const
    {
        return c < a.c;
    }
}a[N];
int n, k;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    k = read(), n = read();
    for(int i = 0; i < n; i ++ ) 
    {
        int c = read(), num = read();
        a[i] = {num, c};
    }

    sort(a, a + n);
    int ans = 0;
    for(int i = 0; i < n; i ++ )
    {
        if(k == 0) break;
        if(k >= a[i].num)
        {
            ans += a[i].num * a[i].c;
            k -= a[i].num;
        }
        else
        {
            ans += k * a[i].c;
            k = 0;
        }
    }

    cout << ans << endl;

    return 0;
}