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

const int N = 1e6 + 50;
ll w[N], dist[N], siz[N];
ll n, K, sum, ans;
int ch[N << 2][2], p[N], p2[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%lld%lld", &n, &K);
    for(int i = 2; i <= n; i ++ )
    {
        int p;
        ll w;
        scanf("%d%lld", &p, &w);
        dist[i] = dist[p] ^ w;
    }

    for(int i = 1; i <= n; i ++ ) p[i] = p2[i] = 1;
    for(int d = 61; d >= 0; d -- )
    {
        int cnt = 0;
        sum = 0;
        for(int j = 1; j <= n; j ++ ) ch[j][0] = ch[j][1] = siz[j] = 0;
        for(int j = 1; j <= n; j ++ )
        {
            int &now = ch[p[j]][dist[j] >> d & 1];
            if(!now) now = ++ cnt;
            siz[p[j] = now] ++;
        }
        for(int j = 1; j <= n; j ++ ) 
            sum += siz[ch[p2[j]][dist[j] >> d & 1]];
        int x = 0;
        if(sum < K) K -= sum, x = 1, ans |= 1ll << d;
        for(int j = 1; j <= n; j ++ )
            p2[j] = ch[p2[j]][(dist[j] >> d & 1) ^ x];
    }

    cout << ans << endl;

    return 0;
}
