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
ll f[N];
ll sumC[N], sumT[N];
int q[N], hh, tt = -1;
ll n, s;
ll L;

struct point
{
    ll x, y;
}p[N];

inline double slope(int a, int b)
{
    return (p[a].y - p[b].y) * 1.0 / (p[a].x - p[b].x);
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), s = read();

    for(int i = 1; i <= n; i ++ )
    {
        int t = read(), c = read();
        sumT[i] = sumT[i - 1] + t;
        sumC[i] = sumC[i - 1] + c;
    }
    
    q[++ tt] = 0;
    for(int i = 1; i <= n; i ++ )
    {
        int k = q[hh];
        if(tt != 0)
        { 
            int l = hh, r = tt;
            while(l < r)
            {
                int mid = l + r >> 1;
                if(f[q[mid]] - f[q[mid + 1]] >= (sumT[i] + s) * (sumC[q[mid]] - sumC[q[mid + 1]])) 
                    l = mid + 1;
                else r = mid;
            }
            k = q[l];
        }
        f[i] = f[k] - (sumT[i] + s) * sumC[k] + sumT[i] * sumC[i] + s * sumC[n];
        p[i] = {sumC[i], f[i]};
        while(hh < tt && (f[q[tt]] - f[q[tt - 1]]) * (sumC[i] - sumC[q[tt]]) >=
                        (f[i] - f[q[tt]]) * (sumC[q[tt]] - sumC[q[tt - 1]])) tt --;
        q[++ tt] = i;
    }

    cout << f[n] << endl;

    return 0;
}