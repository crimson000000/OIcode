#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
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

inline void write(__int128 x)
{
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 1e6 + 10;
ull a[N], sum;
int n, k, m, c;
int p[N], q[N];
bitset<N> restric;

__int128 qmi(__int128 a, __int128 k)
{
    __int128 res = 1;
    while(k)
    {
        if(k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read(), c = read(), k = read();

    for(int i = 1; i <= n; i ++ ) 
    {
        scanf("%llu", &a[i]);
        sum |= a[i];
    }
    
    for(int i = 1; i <= m; i ++ )
    {
        p[i] = read();
        q[i] = read();
        restric[p[i]] = true;
    }

    ull cnt = 0;
    for(int i = 0; i < k; i ++ ) 
    {
        if(!restric[i] || (sum >> i & 1)) cnt ++;
    }

    write((__int128)qmi(2ull, cnt) - n);

    return 0;
}