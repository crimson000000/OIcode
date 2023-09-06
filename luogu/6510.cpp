#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int sn[N], sx[N], a[N];
int n, tn, tx, ans;
int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++ ) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i ++ ){
        while(tn && a[i] <= a[sn[tn]]) tn --;
        while(tx && a[sx[tx]] < a[i]) tx --;
        int k = upper_bound(sn + 1, sn + 1 + tn, sx[tx]) - sn;
        if(k != tn + 1) ans = max(ans, i - sn[k] + 1);
        sn[++ tn] = i;
        sx[++ tx] = i;
    }
    cout << ans << endl;
}