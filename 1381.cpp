#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m, l, ans1, ans2;
string a[N], s;
unordered_map<string, bool> flag;
unordered_map<string, int> sum; 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i ++ ) 
    {
        cin >> s;
        flag[s] = true;
    }
    cin >> m;
    l = 1;
    for(int i = 1; i <= m; i ++ ) 
    {
        cin >> a[i];
        if(flag[a[i]]) sum[a[i]] ++;
        if(sum[a[i]] == 1) ans1 ++, ans2 = i - l + 1;
        while(l <= i)
        {
            if(!flag[a[l]]) 
            {
                l ++;
                continue;
            }
            if(sum[a[l]] >= 2)
            {
                sum[a[l]] --;
                l ++;
                continue;
            }
            break;
        }
        ans2 = min(ans2, i - l + 1);
    }
    cout << ans1 << endl << ans2 << endl;
}