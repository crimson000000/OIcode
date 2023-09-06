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
int primes[N], cnt;
bool st[N];
int l, r;

void init(int n)
{
    for(int i = 2; i <= n; i ++ )
    {
        if(!st[i]) primes[cnt ++ ] = i;
        for(int j = 0; primes[j] <= n / i; j ++ )
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

    l = read(), r = read();
    init(50000);

    memset(st, 0, sizeof st);
    for(int i = 0; i < cnt; i ++ )
    {
        ll p = primes[i];
        for(ll p0 = max(2 * p, (l + p - 1) / p * p); p0 <= r; p0 += p)
            st[p0 - l] = true;
    }

    cnt = 0;
    for(int i = 0; i <= r - l; i ++ )
        if(!st[i] && i + l >= 2) primes[cnt ++ ] = i + l;

    cout << cnt << endl;
    
    return 0;
}
