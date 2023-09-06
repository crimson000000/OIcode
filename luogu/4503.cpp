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
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
ll n, l, s;
const int N = 510, P = 2333, M = 998244353, NN = 30010;
ll h[NN][N];
ll p[N];
vector<ll> w;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read(), l = read(), s = read();
    ll ans = 0;

    p[0] = 1;
    
    for(int i = 1; i <= n; i ++ )
        for(int j = 1; j <= l; j ++ )
        {
            char ch;
            cin >> ch;
            h[i][j] = (h[i][j - 1] * P + ch) ;
        }
    
    p[0] = 1; 
    for(int i = 1; i <= l; i ++ ) p[i] = p[i - 1] * P;

    for(int i = 1; i <= l; i ++ )
    {
        w.clear();
        for(int j = 1; j <= n; j ++ )
        {
            ll hsh = (h[j][l] - (h[j][i] - h[j][i - 1] * P) * p[l - i] - h[j][i - 1] * (p[l - i + 1] - p[l - i]));
            w.push_back(hsh);
        }
        sort(w.begin(), w.end());
        ll tmp = 1;
        for(int j = 0; j < w.size(); j ++ )
        {
            if(w[j] != w[j + 1]) tmp = 1;
            else
            {
                ans += tmp;
                tmp ++;
            }
        }
    }

    cout << ans << endl;

    return 0;
}
