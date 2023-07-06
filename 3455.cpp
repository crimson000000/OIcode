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

const int N = 1e5 + 10;
int primes[N], cnt;
bool st[N];
int miu[N];
int sum[N];
int T;

void init(int n)
{
    miu[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i])
        {
            primes[cnt ++ ] = i;
            miu[i] = -1;
        }
        for(int j = 0; primes[j] <= n / i; j ++ )
        {
            st[primes[j] * i] = true;
            if(i % primes[j] == 0)
            {
                miu[i * primes[j]] = 0;
                break;
            }
            miu[i * primes[j]] = miu[i] * -1;
        }
    }

    for(int i = 1; i <= n; i ++ ) sum[i] = sum[i - 1] + miu[i];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    T = read();

    init(N - 1);

    while(T -- )
    {
        int a = read(), b = read(), d = read();
        ll res = 0;

        a /= d, b /= d;
        int n = min(a, b);
        for(int l = 1, r; l <= n; l = r + 1)
        {
            r = min(n, min(a / (a / l), b / (b / l)));
            res += (sum[r] - sum[l - 1]) * (ll)(a / l) * (b / l);
        }

        cout << res << endl;
    }
    
    return 0;
}
