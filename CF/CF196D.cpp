#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using u128 = __uint128_t;
using PII = pair<ll, ll>;

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
const u128 P = 9223372036854775783;
u128 ppow[N];
u128 h1[N], h2[N];
char s[N];
int n, d, pos;

inline bool check(int l, int r)
{
    u128 a = (h1[r] - h1[l - 1] * ppow[r - l + 1]) * ppow[l - 1];
    u128 b = h2[r] - h2[l - 1];
    return a == b;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    d = read();
    scanf("%s", s + 1);
    n = strlen(s + 1);

    ppow[0] = 1;
    for(int i = 1; i <= n; i ++ ) ppow[i] = ppow[i - 1] * P;
    
    pos = n;
    for(int i = 1; i <= n; i ++ )
    {
        h1[i] = h1[i - 1] * P + s[i];
        h2[i] = h2[i - 1] + s[i] * ppow[i - 1];
        if(i >= d && check(i - d + 1, i))
        {
            pos = i;
            break;
        } 
        if(i >= d + 1 && check(i - d, i))
        {
            pos = i;
            break;
        }
    }

    bool flag = false;
    for(int i = pos; i; i -- )
    {
        for(char c = s[i] + 1; c <= 'z'; c ++ )
        {
            s[i] = c;
            h1[i] = h1[i - 1] * P + s[i];
            h2[i] = h2[i - 1] + s[i] * ppow[i - 1];
            if(i >= d && check(i - d + 1, i)) continue;
            if(i >= d + 1 && check(i - d, i)) continue;
            flag = true;
            break;
        }
        if(flag)
        {
            pos = i;
            break;
        }
    }

    if(!flag)
    {
        puts("Impossible");
        return 0;
    }

    for(int i = pos + 1; i <= n; i ++ )
    {
        for(char c = 'a'; c <= 'z'; c ++ )
        {
            s[i] = c;
            h1[i] = h1[i - 1] * P + s[i];
            h2[i] = h2[i - 1] + s[i] * ppow[i - 1];
            if(i >= d && check(i - d + 1, i)) continue;
            if(i >= d + 1 && check(i - d, i)) continue;
            break;
        }
    }

    puts(s + 1);

    return 0;
}