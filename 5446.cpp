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

const int N = 1e7 + 10;
char s[N];
int f[N];
bitset<N> vis;
int n;

void manacher()
{
    s[0] = '#', s[n + 1] = '?';
    int mid = 0, r = 1;
    for(int i = 1; i <= n; i ++ )
    {
        if(i > r) f[i] = 1;
        else f[i] = min(f[2 * mid - i], r - i);
        while(s[i + f[i]] == s[i - f[i]]) f[i] ++;
        if(i + f[i] > r) r = i + f[i], mid = i;
    }
    for(int i = 1; i <= n; i ++ ) 
        f[i] --;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    int T = read();
    while(T -- )
    {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        manacher();
        for(int i = n; i; i -- )
        {
            vis[i] = 0;
            if(i + f[i] == n) vis[i] = true;
            if(i - f[i] == 1 && vis[i + f[i]])
                vis[i] = true;
        }
       for(int i = 1; i <= n; i ++ )
            if(vis[i])
                cout << i << ' ';
        puts("");
    }

    return 0;
}