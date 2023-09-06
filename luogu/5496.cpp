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

const int N = 1e6 + 10;
char s[N];
int t[N][26], fail[N];
int num[N], len[N];
int idx;
int n, last, cur;

int getfail(int x, int i)
{
    while(i - len[x] < 1 || s[i - len[x] - 1] != s[i]) x = fail[x];
    return x;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);
    n = strlen(s + 1);
    fail[0] = 1, len[1] = -1;
    idx = 1;
    for(int i = 1; i <= n; i ++ )
    {
        s[i] = (s[i] - 97 + last) % 26 + 97;
        int pos = getfail(cur, i);
        if(!t[pos][s[i] - 'a'])
        {
            fail[++ idx] = t[getfail(fail[pos], i)][s[i] - 'a'];
            t[pos][s[i] - 'a'] = idx;
            len[idx] = len[pos] + 2;
            num[idx] = num[fail[idx]] + 1;
        }
        cur = t[pos][s[i] - 'a'];
        last = num[cur];
        printf("%d ", last);
    }

    return 0;
}