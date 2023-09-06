#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
using u128 = __uint128_t;

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
const u128 P = 1000000007;
struct my_hash {
    static u128 splitmix64(u128 x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(u128 x) const {
        static const u128 FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

unordered_map<u128, int, my_hash> mp;
u128 ppow[N];
u128 h[N];
int m;
char s[N];
set<int> Len;
int cnt[N];

u128 gethash(char *s)
{
    u128 res = 0;
    for(int i = 1; s[i]; i ++ )
        res = res * P + s[i];
    return res;
}

void Hash(char *s)
{
    for(int i = 1; s[i]; i ++ )
        h[i] = h[i - 1] * P + s[i];
}

u128 get(int l, int r)
{
    return h[r] - h[l - 1] * ppow[r - l + 1];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    m = read();
    ppow[0] = 1;
    for(int i = 1; i < N - 5; i ++ ) ppow[i] = ppow[i - 1] * P;

    while(m -- )
    {
        int op = read();
        scanf("%s", s + 1);
        if(op == 1)
        {
            mp[gethash(s)] ++;
            int len = strlen(s + 1);
            Len.insert(len);
            cnt[len] ++;
        }
        else if(op == 2)
        {
            mp[gethash(s)] --;
            int len = strlen(s + 1);
            cnt[len] --;
            if(!cnt[len]) Len.erase(len);
        }
        else
        {
            Hash(s);
            int ans = 0;
            int n = strlen(s + 1);
            for(auto len : Len)
            {
                // cout << len << ' ';
                for(int i = 1; i <= n - len + 1; i ++ )
                {
                    u128 hsh = get(i, i + len - 1);
                    if(mp.count(hsh)) ans += mp[hsh];
                }
            }
            // puts("");
            printf("%d\n", ans);
        }

        fflush(stdout);
    }

    return 0;
}