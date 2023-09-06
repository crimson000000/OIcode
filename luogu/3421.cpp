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

const int N = 110;
int a[N], b[N];
int n;

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    a[1] = read(), b[1] = read();
    for(int i = 2; i <= n; i ++ )
    {
        a[i] = read(), b[i] = read();
        while(a[i])
        {
            if(abs(a[1]) < abs(a[i])) swap(a[i], a[1]), swap(b[i], b[1]);
            else b[1] -= b[i] * (a[1] / a[i]), a[1] %= a[i];
        }
        if(i > 2) b[2] = gcd(b[2], b[i]), b[1] %= b[2];
    }

    printf("%d %d\n%d %d\n", a[1], b[1], a[2], b[2]);

    return 0;
}