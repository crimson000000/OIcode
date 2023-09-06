#define LOCAL
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using PII = pair<ll, ll>;
using i128 = __int128;

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

void write(i128 x)
{
    if(x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 1e6 + 10;
string s;
i128 ans;
ll w[N];
i128 sum;
int stk[N], tt = 1;
int nxt[N], anc[N];
map<ll, int> cnt;
int n;

ll query(int p)
{
    return w[*lower_bound(stk + 1, stk + tt + 1, p)];
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    char ch[2];
    scanf("%s", ch);
    w[0] = read();

    s += ch[0];
    ans = w[0];

    // write(1028);
    
    write(ans), puts("");

    for(int i = 1, j = 0; i < n; i ++ )
    {
        char c = getchar();
        c = (c + (ans % 26) - 'a') % 26 + 'a';
        s += c;

        w[i] = read();
        w[i] ^= (ans & ((1 << 30) - 1));
        // cout << w[i] << endl;
        while(j > 0 && c != s[j]) j = nxt[j];
        if(c == s[j]) j ++;
        nxt[i + 1] = j;

        if(c == s[nxt[i]]) anc[i] = anc[nxt[i]];
        else anc[i] = nxt[i];
        
        for(int k = i; k > 0; )
        {
            if(s[k] == c) k = anc[k];
            else
            {
                ll v = query(i - k);
                cnt[v] --;
                if(!cnt[v]) cnt.erase(v);
                sum -= v;
                k = nxt[k];
            }
        }

        if(s[0] == c)
        {
            sum += w[i];
            cnt[w[i]] ++;
        }

        while(tt > 0 && w[i] <= w[stk[tt]]) tt --;
        stk[++ tt] = i;
        int tot = 0;
        for(auto it = cnt.upper_bound(w[i]); it != cnt.end(); )
        {
            sum -= (it -> first - w[i]) * it -> second;
            tot += it -> second;
            auto j = next(it);
            cnt.erase(it);
            it = j;
        }

        // write(stk[1]), putchar(' ');

        cnt[w[i]] += tot;
        ans += sum + w[stk[1]];
        write(ans), puts("");
    }

    // cout << s << endl;

    return 0;
}