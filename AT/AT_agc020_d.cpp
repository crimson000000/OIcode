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

ll A, B, C, D, k;
ll a, b;

inline void getab(ll p)
{
    a = A - p / (k + 1) * k - p % (k + 1);
    b = B - p / (k + 1);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        A = read(), B = read(), C = read(), D = read();
        k = max((A + B) / (B + 1), ((A + B) / (A + 1)));

        ll l = 0, r = A + B;
        while(l < r)
        {
            ll mid = l + r >> 1;
            getab(mid);
            if(b <= a * k) l = mid + 1;
            else r = mid;
        }

        getab(l);
        r = l + 1 + b - a * k;

        for(int i = C; i <= D; i ++ )
        {
            if(i <= l) 
            {
                if(i % (k + 1) == 0) putchar('B');
                else putchar('A');
            }
            else
            {
                if((i - r) % (k + 1) == 0) putchar('A');
                else putchar('B');
            }
        }
        puts("");
    }

    return 0;
}