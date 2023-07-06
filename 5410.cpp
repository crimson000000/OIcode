#include <bits/stdc++.h>
using namespace std;
const int N = 2e7 + 10;
string a, b;
long long ans1, ans2;
int ne[N << 1];

void getnext(string s)
{
    for(int i = 1, l, r = 0; i < s.size(); i ++ )
    {
        if(i < r) ne[i] = min(ne[i - l], r - i);
        while(s[ne[i]] == s[i + ne[i]] && i + ne[i] < s.size()) ne[i] ++;
        if(i + ne[i] > r) l = i, r = i + ne[i];
    }
}


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> a >> b;
    getnext(b + a);
    ans1 ^= 1ll * (b.size() + 1) * (0+1);
    for(int i = 1; i < b.size(); i ++ )
        ans1 ^= (long long)(min<int>(ne[i], b.size() - i) + 1) * (i + 1);
    for(int i = 0; i < a.size(); i ++ ) ans2^=1ll*(min<int>(ne[i+b.size()],b.size())+1)*(i+1);
    cout << ans1 << endl << ans2 << endl;
}