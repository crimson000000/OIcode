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

const int N = 5e5 + 10;
char s[N];
int f[N], t[N];
int ne[N];

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    scanf("%s", s + 1);

    int n = strlen(s + 1);
    for(int i = 2, j = 0; i <= n; i ++ )
    {
        while(j && s[j + 1] != s[i]) j = ne[j];
        if(s[j + 1] == s[i]) j ++;
        ne[i] = j;
    }

    f[1] = 1, t[1] = 1;
    for(int i = 2; i <= n; i ++ )
    {
        f[i] = i;
        if(t[f[ne[i]]] >= i - ne[i]) f[i] = f[ne[i]];
        t[f[i]] = i;
    }

    cout << f[n] << endl;

    return 0;
}
