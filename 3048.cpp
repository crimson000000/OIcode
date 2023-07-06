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

const int N = 1e7 + 10;
bitset<N> ans;

int n, k;
int highest;

int C(int n, int m)
{
    int res = 1, o = 1;
    for(int i = n - m + 1; i <= n; i ++ )
    {
        res = res * i / o;
        o ++;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), k = read();
    highest = k;

    while(1)
    {
        int x = C(highest - 1, k - 1);
        if(n > x) n -= x;
        else break;
        highest ++;
    } 

    ans[highest] = 1;
    k --;

    for(int i = highest - 1; i; i -- )
    {
        int x = C(i - 1, k);
        if(n > x)
        {
            n -= x;
            k --;
            ans[i] = 1;
        }
    }

    for(int i = highest; i; i -- ) 
        if(ans[i])
            putchar('1');
        else putchar('0'); 

    return 0;
}