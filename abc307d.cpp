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
int ne[N], stk[N], tt = -1;
int n;

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    scanf("%s", s + 1);

    for(int i = 1; i <= n; i ++ )
    {
        if(s[i] == '(') stk[++ tt] = i;
        if(s[i] == ')')
        {
            if(tt == -1) continue;
            ne[stk[tt]] = i;
            tt --;
        }
    }

    for(int i = 1; i <= n; i ++ )
    {
        if(ne[i]) i = ne[i];
        else putchar(s[i]);
    }

    return 0;
}