#include <bits/stdc++.h>
using namespace std;
const int N = 20, INF = 1145141919, Base = 114;
typedef unsigned long long ULL;
int lim[N], a[N][N], b[N][N];
map<ULL, int> mp;
int n, m;

ULL zip(){
    ULL res = 0;
    for(int i = 1; i <= n; i ++ ) res = res * Base + lim[i];
    return res;
}

void unzip(ULL x){
    for(int i = n; i; i -- ) 
        lim[i] = x % Base, x /= Base;
}

int getnxt(){
    int ret = 0;
    for(int i = 1; i <= n; i ++ ) ret += lim[i];
    return ret & 1;
}

int dfs(ULL now){
    if(mp.find(now) != mp.end()) return mp[now];
    unzip(now);

    int f = getnxt();
    int res = f ? INF: -INF;

    for(int i = 1; i <= n; i ++ ){
        if(lim[i] < lim[i - 1]){
            lim[i] ++ ;
            ULL nw = zip();
            if(!f) res = max(res, dfs(nw) + a[i][lim[i]]);
            else res = min(res, dfs(nw) - b[i][lim[i]]); 
            lim[i] --;
        }
    } 
    return mp[now] = res;
}

int main(){
    scanf("%d%d", &n, &m);

    for(int i = 1; i <= n; i ++ ) 
        for(int j = 1; j <= m; j ++ )
            scanf("%d", &a[i][j]);

    for(int i = 1; i <= n; i ++ ) 
        for(int j = 1; j <= m; j ++ )
            scanf("%d", &b[i][j]);
    lim[0] = m;
    for(int i = 1; i <= n; i ++ ) lim[i] = m;
    ULL FULL = zip();
    mp[FULL] = 0;
    dfs(0);
    cout << mp[0] << endl;
    return 0;
}