#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10, M = 1e9 + 7;
char s[N];
int n, num[N], len, ne[N];
long long ans;

void kmp()
{
    for(int i = 2, j = 0; i <= len; i ++ )
    {
        while(j && s[i] != s[j + 1]) j = ne[j];
        if(s[i] == s[j + 1]) j ++;
        ne[i] = j;
        num[i] = num[j] + 1;
    }
}

void getsum()
{
    for(int i = 2, j = 0; i <= len; i ++ )
    {
        while(j && s[i] != s[j + 1]) j = ne[j];
        if(s[i] == s[j + 1]) j ++;
        while(j * 2 > i) j = ne[j];
        ans = ans * (num[j] + 1) % M;
    }
}

int main()
{
    scanf("%d", &n);
    while(n -- )
    {
        ans = 1, num[1] = 1;
        scanf("%s", s + 1);
        len = strlen(s + 1);
        kmp();
        getsum();
        cout << ans << endl;
    }
    return 0;
}