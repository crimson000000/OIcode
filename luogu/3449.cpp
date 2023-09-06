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

const int N = 2e6 + 10, mod = 998244353, P = 131;
int tr[N][26], idx = 1;
vector<int> id[N];
ll hsh[N], bhsh[N];
string s[N];
ll ppow[N];
int n;
ll ans;

inline void insert(string s, int idd)
{
    int p = 1;
    for(int i = 1; i < s.size(); i ++ )
    {
        int u = s[i] - 'a';
        if(!tr[p][u]) tr[p][u] = ++ idx;
        p = tr[p][u];
    }
    id[p].emplace_back(idd);
}

inline ll gethash(string s)
{
    ll res = 0;
    for(int i = 1; i < s.size(); i ++ )
        res = (res * P % mod + s[i]) % mod;
    return res;
}

inline bool check(int a, int b)
{
    // cout << a << ' ' << b << endl;
    ll front = (hsh[a] * ppow[s[b].size() - 1] % mod + hsh[b]) % mod;
    ll back = (bhsh[b] * ppow[s[a].size() - 1] % mod + bhsh[a]) % mod;
    // cout << front << ' ' << back << endl;
    return front == back;
}

inline void vis(int now)
{
    int p = 1;
    for(int i = 1; i < s[now].size(); i ++ )
    {
        int u = s[now][i] - 'a';
        p = tr[p][u];
        for(auto v : id[p])
        {
            if(check(now, v)) ans ++;
            if(check(v, now)) ans ++;
        }
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    ppow[0] = 1;
    for(int i = 1; i < N; i ++ ) 
        ppow[i] = ppow[i - 1] * P % mod;

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        int _ = read();
        cin >> s[i];
        s[i] = " " + s[i];
        insert(s[i], i);
        hsh[i] = gethash(s[i]);

        reverse(s[i].begin() + 1, s[i].end());
        bhsh[i] = gethash(s[i]);

        reverse(s[i].begin() + 1, s[i].end());
    }

    // cout << bhsh[1] << endl;
    // cout << gethash("aaaaa") << endl;
    // cout << check(1, 3) << endl;

    for(int i = 1; i <= n; i ++ )
        vis(i);

    cout << ans - n << endl;

    return 0;
}
