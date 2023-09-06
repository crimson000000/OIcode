#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
typedef unsigned long long ull;
typedef unsigned short us;

inline ll read()
{
    ll x;
    cin >> x;
    return x;
}

const int N = 400010;
bool s[N+1][256];
ull lastans;

ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void Genshin_Impact(int n, ull a1, ull a2) {
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < 256; j++)
            s[i][j] = (myRand(a1, a2) & (1ull << 32)) ? 1 : 0;
}

ull n, m, a1, a2;
us a[N][16], q[16];
int popcnt[65537];
vector<int> pos[16][65537];
char t[N];
int k;

inline void write(ull a[])
{
    for(int i = 0; i < 16; i ++ )
        for(int j = 15; j >= 0; j -- )
            if(a[i] >> j & 1)
                putchar('1');
            else putchar('0');
    puts("");
}

inline us trans(char s)
{
    if(s >= '0' && s <= '9') return s - '0';
    else
    {
        if(s == 'A') return 10;
        if(s == 'B') return 11;
        if(s == 'C') return 12;
        if(s == 'D') return 13;
        if(s == 'E') return 14;
        return 15;
    }
}

inline int Count(us a[], us b[])
{
    int res = 0;
    for(int i = 0; i < 16; i ++ )
        res += popcnt[a[i] ^ b[i]];
    return res;
}

inline bool check(int b, ull x)
{
    for(auto p : pos[b][x])
        if(Count(a[p], q) <= k) return true;
    return false;
}

inline void solve()
{
    int cur = 0;
    for(int i = 0; i < 16; i ++ )
    {
        q[i] = 0;
        for(int j = 0; j < 4; j ++ )
        {
            q[i] <<= 4;
            q[i] |= trans(t[cur]);
            cur ++;
        }
        if(lastans) q[i] ^= 65535;
    }

    // write(q);

    for(int i = 0; i < 16; i ++ )
    {
        if(check(i, q[i]))
        {
            puts("1");
            lastans = 1;
            return;
        }
    }

    puts("0");
    lastans = 0;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%llu%llu%llu%llu", &n, &m, &a1, &a2);
    Genshin_Impact(n, a1, a2);

    int cur = 0, tt = 0;
    for(int i = 1; i <= n; i ++ )
    {
        cur = 0;
        tt = 0;
        for(int j = 0; j < 16; j ++ )
        {
            for(int k = 0; k < 16; k ++ )
            {
                a[i][cur] <<= 1;
                a[i][cur] |= s[i][tt];
                tt ++;
            }
            pos[j][a[i][cur]].emplace_back(i);
            cur ++;
        }
    }

    // for(int i = 1; i <= n; i ++ ) 
    // {
    //     for(int j = 0; j < 256; j ++ )
    //         putchar('0' + s[i][j]);
    //     puts("");
    // }

    // for(int i = 1; i <= n; i ++ )
    //     write(a[i]);

    for(int i = 1; i <= 65535; i ++ )
        popcnt[i] = popcnt[i - (i & -i)] + 1;
    
    while(m -- )
    {
        scanf("%s", t);
        scanf("%d", &k);
        solve();
    }

    return 0;
}