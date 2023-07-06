#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 1e6 + 10;
int n, ne[N];
char s[N];
ull ans;

int main()
{
    cin >> n >> s + 1;
    for(int i = 2, j = 0; i <= n; i ++ )
    {
        while(j && s[i] != s[j + 1]) j = ne[j];
        if(s[i] == s[j + 1]) j ++;
        ne[i] = j;
    }
    for(int i = 2, j = 2; i <= n; i ++, j = i)
    {
        while(ne[j]) j = ne[j];
        if(ne[i]) ne[i] = j;
        ans += i - j;
    }
    cout << ans << endl;
}