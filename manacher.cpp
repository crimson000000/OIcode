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
const int N = 11000010;
char s[N * 2], t[N];
int f[N * 2];
int n, ans;

void manacher(int len)
{
    s[0] = '@', s[1] = '#';
    for(int i = 1; i <= len; i ++ )
        s[i << 1] = t[i], s[i << 1 | 1] = '#';
    len = len << 1 | 1, s[len + 1] = '$';
    int mid = 0, r = 1; 
    for(int i = 1; i <= len; i ++ )
    {
        if(i > r) f[i] = 1;
        else f[i] = min(r - i, f[2 * mid - i]);
        while(s[i + f[i]] == s[i - f[i]]) f[i] ++ ;
        ans = max(ans, f[i]);
        if(i + f[i] > r) r = i + f[i], mid = i;
    }
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif
    scanf("%s", t + 1);
    int len = strlen(t + 1);
    manacher(len);

    cout << ans - 1 << endl;
   
    return 0;
}



