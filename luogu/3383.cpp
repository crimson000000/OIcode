#define LOCAL
#include <bits/stdc++.h>

using namespace std;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

using ll = long long;

auto read = []()
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
};

const int N = 1e8 + 10;

static int primes[N], cnt;
static bitset<N> st;

static int n, q;

auto init = [](int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[++ cnt] = i;
        }
        for(int j = 1; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0) break;
        }
    }
};

auto mian = [&]()
{
    n = read(), q = read();

    init(n);

    while(q -- )
    {
        int k = read();
        printf("%d\n", primes[k]);
    }
};

mian();

    return 0;
}