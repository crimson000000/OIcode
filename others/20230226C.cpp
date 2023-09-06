#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> PII;

inline ll read()
{
    ll x = 0, f = 1;
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

const int N = 250010;
PII f[N][21];
ll s[N];
int n, L, R;
PII ans;
double av;

PII min(PII a, PII b)
{
    if(a.first != b.first)
        if(a.first > b.first)
            return b;
        else return a;
    else
        if(a.second > b.second) 
            return a;
        else return b;
}

void ST_pre()
{
    int t = log2(n) + 1;
    for(int i = 1; i <= n; i ++ ) f[i][0] = {s[i], i};
    for(int i = 1; i <= t; i ++ )
        for(int j = 1; j + (1 << i) - 1 <= n; j ++ )
            f[j][i] = min(f[j][i - 1], f[j + (1 << i - 1)][i - 1]);
}

PII query(int l, int r)
{
    int t = log2(r - l + 1);
    return min(f[l][t], f[r - (1 << t) + 1][t]);
}

ll gcd(ll a, ll b)
{
    if(b != 0) return gcd(b, a % b);
    return a;
}

void yf(PII &x)
{
    int gc = gcd(x.first, x.second);
    x.first /= gc;
    x.second /= gc;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), L = read(), R = read();
    for(int i = 1; i <= n; i ++ )
    {
        s[i] = read();
        s[i] += s[i - 1];
    }
    
    if(n <= 30000)
    {
        for(int i = 1; i <= n; i ++ )
        {
            int ql = max(i - R, 0), qr = max(i - L, 0);
            for(int j = ql; j <= qr; j ++ )
            {
                if(j != i)
                {
                    double ave = (double)(s[i] - s[j]) / (i - j);
                    if(ave > av)
                    {
                        av = ave;
                        ans = {s[i] - s[j], i - j};
                    }
                }
            }
        }
    }
    
    if(n >= 30000)
    {
        ST_pre();

        for(int i = 1; i <= n; i ++ )
        {
            int ql = max(i - R, 0), qr = max(i - L, 0);
            PII q = query(ql, qr);
            ll t = q.first, pos = q.second;
            double ave = (double)(s[i] - t) / (i - pos);
            if(av < ave)
            {
                av = ave;
                ans = {s[i] - t, i - pos};
            }
        }
    }

    bool flag = false;
    if(ans.first < 0)
    {
        flag = true;
        ans.first = abs(ans.first);
    }

    yf(ans);

    if(flag) cout << "-";
    printf("%lld/%lld\n", ans.first, ans.second);

    return 0;
}
