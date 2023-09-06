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

int x;

void divide(int x)
{
    for(int i = 14; i >= 0; i -- )
    {
        if((1ll << i) <= x)
        {
            if(i == 1) putchar('2');
            else if(i == 0) cout << "2(0)";
            else
            {
                printf("2(");
                divide(i);
                putchar(')');
            }
            x -= (1 << i);
            if(x) putchar('+');
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> x;
    divide(x);

    return 0;
}