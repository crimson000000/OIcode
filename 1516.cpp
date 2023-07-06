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

ll x, y, n, m, l;

/*ll exgcd(ll a, ll b, ll &x, ll &y)
{
    if(!b)
    {
        x = 1, y = 0;
        return a;
    }
    ll d = exgcd(b, a % b, x, y), z = x;
    x = y, y = z - (a / b) * y;
    return d;
}*/

ll exgcd(ll a, ll b, ll &x, ll &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	ll d = exgcd(b, a % b, x, y), z = x;
	x = y, y = z - y * (a / b);
	return d;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    cin >> x >> y >> m >> n >> l;
    ll a = m - n, b = l, c = y - x;
    ll t, k;
    
    if(a < 0)
    {
        a = -a, c = -c;
    }

    ll d = exgcd(a, b, t, k);
    if(c % d == 0)
    {
        ll mod = b / d;

        t = (t * (c / d) % mod + mod) % mod;
        cout << t << endl;
    }
    else puts("Impossible");
       
    return 0;
}
