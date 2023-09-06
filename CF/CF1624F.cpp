#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;

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

int n;

int ask(int x)
{
    printf("+ %d\n", x);
    fflush(stdout);
    int res = read();
    return res;
}

int main()
{
    // #ifdef LOCAL
    //     freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
    //     freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    // #endif

    n = read();
    int l = 1, r = n;

    while(l + 1 < r)
    {
        int mid = l + r >> 1;
        int a = n - mid % n;
        if(ask(a) == (l + a) / n) r = mid;
        else l = mid;
        r += a, l += a;
    }

    printf("! %d\n", l);
    fflush(stdout);
    
    return 0;
}
