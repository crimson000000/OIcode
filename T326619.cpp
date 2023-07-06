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
bitset<N> col, app;
bool flag;
int n, m;

inline int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), m = read();
    while(m -- )
    {
        int x = read();
        int d = gcd(x, n);
        if(app[d] || flag) printf("0 ");
        else
        {
            app[d] = true;
            int cnt = 0;
            for(int i = 0; i < n; i += d) 
                if(!col[i])
                {
                    col[i] = true;
                    cnt ++;
                }
            printf("%d ", cnt);
        }
        if(d == 1) flag = true;
    }

    return 0;
}