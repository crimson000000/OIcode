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

const int N = 110;
char s[N][N];
int len[N];
int n;

char t[N];

inline bool check(int x, int y)
{
    for(int i = 1; i <= len[x]; i ++ ) t[i] = s[x][i];
    for(int i = len[x] + 1; i <= len[x] + len[y]; i ++ )
        t[i] = s[y][i - len[x]];
    
    int lent = len[x] + len[y];
    for(int i = 1; i <= lent; i ++ )
    {
        if(t[i] != t[lent - i + 1])
            return false;
    }
    return true;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ )
    {
        scanf("%s", s[i] + 1);
        len[i] = strlen(s[i] + 1);
    }

    for(int i = 1; i <= n; i ++ )
    {
        for(int j = 1; j <= n; j ++ )
        {
            if(i == j) continue;
            if(check(i, j))
            {
                puts("Yes");
                return 0;
            }
        }
    }

    puts("No");

    return 0;
}