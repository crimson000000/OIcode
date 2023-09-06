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

const int N = (1 << 20) + 10;
char s[N];
int ne[N];
ll ans, pre[N], per[N], suf[N];
int tmp[28];
int n;

void solve()
{
    memset(pre, 0, sizeof pre);
    memset(per, 0, sizeof per);
    memset(suf, 0, sizeof suf);
    memset(ne, 0, sizeof ne);
    ans = 0;

    scanf("%s", s + 1);
    n = strlen(s + 1);
    for(int i = 2, j = 0; i <= n; i ++ )
    {
        while(j && s[j + 1] != s[i]) j = ne[j];
        if(s[j + 1] == s[i]) j ++;
        ne[i] = j;
    }

    memset(tmp, 0, sizeof tmp);
    for(int i = n; i; i -- )
    {
        tmp[s[i] - 'a'] ++;
        if(tmp[s[i] - 'a'] & 1)
            suf[i] = suf[i + 1] + 1;
        else suf[i] = suf[i + 1] - 1;
    }

    memset(tmp, 0, sizeof tmp);
    for(int i = 1; i <= n; i ++ )
    {
        tmp[s[i] - 'a'] ++;
        if(tmp[s[i] - 'a'] & 1)
            pre[i] = pre[i - 1] + 1;
        else pre[i] = pre[i - 1] - 1;
    }

    for(int i = 1; i < n; i ++ )
    {
        if(i >= 2)
        {
            ans += per[suf[i + 1]];
            for(int j = i + i; j < n; j += i)
            {
                int T = j - ne[j];
                if(i % T == 0) ans += per[suf[j + 1]];
                else break;
            }
        }
        for(int j = pre[i]; j <= 26; j ++ )
            per[j] ++;
        // printf("%d: ", i);
        // for(int j = 0; j <= 26; j ++ )
        //     printf("%d ", per[j]);
        // puts("");
    }
    cout << ans << endl;
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
        solve();
    }

    return 0;
}