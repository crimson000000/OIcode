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

const int N = 2e6 + 10;
ll f[N];
ll a[N], c[N];
int T, n;

priority_queue<ll, vector<ll>, greater<ll>> heap0, heap1;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    T = read();
    while(T -- )
    {
        while(heap0.size()) heap0.pop();
        while(heap1.size()) heap1.pop();
        memset(f, 0, sizeof f);
        memset(a, 0, sizeof a);
        memset(c, 0, sizeof c);

        n = read();
        for(int i = 1; i <= n; i ++ ) a[i] = read();
        for(int i = 1; i <= n; i ++ ) c[i] = read();

        for(int i = 1; i <= n; i ++ )
        {
            if(c[i] == 0)
            {
                if(!heap0.size()) f[i] = f[i - 1] + a[i] + a[i];
                else 
                {
                    ll val = heap0.top();
                    f[i] = min(val + a[i], f[i - 1] + a[i] + a[i]);
                }
                heap0.push(f[i - 1] + a[i]);
            }
            else
            {
                if(!heap1.size()) f[i] = f[i - 1] + a[i] + a[i];
                else 
                {
                    ll val = heap1.top();
                    f[i] = min(val + a[i], f[i - 1] + a[i] + a[i]);
                }
                heap1.push(f[i - 1] + a[i]);
            }
       }

    //    for(int i = 1; i <= n; i ++ ) cout << f[i] << ' ';
    //    puts("");
       
       printf("%lld\n", f[n]);
    }

    return 0;
}
