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

const int mod = 1e9 + 9;
ll n;

ll qmi(ll a, ll b, ll p)
{
    ll res = 1;
    while(b)
    {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T;
    cin >> T;
    while(T -- )
    {
        cin >> n;
        if(n == 0) cout << 0 << endl;
        else if(n == 1) cout << 1 << endl; 
        else cout << n * qmi(n, n - 2, mod) % mod << endl;
    }
    
    return 0;
}
