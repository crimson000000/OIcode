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
bitset<N> st;
int primes[N], cnt;
int a[N];
int type;

ll qmi(ll a, ll b, ll p)
{
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

void init(int n)
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
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    init(100001);
    st[4] = false;

    type = read();
    int T = read();

    while(T -- )
    {
        int n = read();
        if(type == 1)
        {
            if(n == 1)
            {
                puts("2 1");
                continue;
            }
            if(n & 1) puts("0");
            else
            {
                printf("2 ");
                for(int i = 0; i < n; i ++ )
                {
                    if(!(i & 1)) printf("%d ", n - i);
                    else printf("%d ", i);
                }
                puts("");
            }
        }
        else
        {
            if(st[n]) puts("0");
            else
            {
                printf("2 1 ");
                if(n == 4)
                {
                    printf("3 2 4\n");
                    continue;
                }
                for(int i = 2; i < n; i ++ )
                {
                    printf("%d ", (ll)i * qmi(i - 1, n - 2, n) % n);
                }
                printf("%d\n", n);
            }
        }
    }

    return 0;
}