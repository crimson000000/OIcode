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

const int N = 1e6 + 10, mod = 1e9 + 9;
ll f[N];
int b[N], w[N];
int n;
char s[N];
int L[N], R[N];
vector<int> nxt[N];

struct ta
{
    ll c[N];
    #define lowbit(x) x & -x

    inline void add(int x, int v)
    {
        x ++;
        for(; x < N - 5; x += lowbit(x)) c[x] = (c[x] + v) % mod;
    }

    inline ll query(int x)
    {
        ll res = 0;
        x ++;
        for(; x; x -= lowbit(x)) res = (res + c[x]) % mod;
        return res;
    }
}bit;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    
    scanf("%s", s + 1);
    n = strlen(s + 1);

    for(int i = 1; i <= n; i ++ )
    {
        if(s[i] == 'B') w[i] = 0;
        else w[i] = w[i - 1] + 1;
    }

    for(int i = n; i >= 0; i -- )
    {
        if(s[i] == 'W') b[i] = 0;
        else b[i] = b[i + 1] + 1;
    }

    for(int i = 0; i <= n; i += 2)
        if(s[i] != 'B' && s[i + 1] != 'W')
        {
            L[i] = i + 2, R[i] = min(n + 1, i + 2 + 2 * b[i + 1]);
            nxt[L[i]].emplace_back(i);
            nxt[R[i]].emplace_back(i);
        }

    // cout << "yeah" << endl;

    f[0] = 1;
    for(int i = 2; i <= n; i += 2)
    {
        for(auto v : nxt[i])
        {
            if(L[v] == i) bit.add(v, f[v]);
            else bit.add(v, mod - f[v]);
        }
        
        if(s[i] != 'B')
        {
            int l = max(-1, i - w[i] * 2 - 2), r = i - 2;
            f[i] = (bit.query(r) - bit.query(l) + mod) % mod;
        }
    }

    cout << f[n] << endl;

    return 0;
}
