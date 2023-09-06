#include<bits/stdc++.h>
using namespace std;
const int N = 20;
double x[N], y[N];
int n;
double dp[1 << 17][N];
double vis[N];
double ans = 1e10;

double squ(double x){
	return x * x;
}

double dist(double x1, double y1, double x2, double y2){
	return sqrt( squ(x1 - x2) + squ(y1 - y2) );
}

void dfs(int t, int now, double s, int b){
	if(s > ans) return;
	
	if(t == n){
		ans = min(ans, s);
	}
	
	for(int i = 1; i <= n; i ++ ){
		if(vis[i]) continue;
		
		int p = b + (1 << (i - 1));
		if(dp[p][i] != 0 && dp[p][i] <= s + dist(x[now], y[now], x[i], y[i])) continue;
		vis[i] = true;
		dp[p][i] = s + dist(x[now], y[now], x[i], y[i]);
		dfs(t + 1, i, dp[p][i], p);
		vis[i] = false;
	}
	
}

int main(){
	scanf("%d", &n);
	
	x[0] = 0, y[0] = 0;
	
	for(int i = 1; i <= n; i ++ ) scanf("%lf%lf", &x[i], &y[i]);
	
	dfs(0, 0, 0, 0);
	
	printf("%.2lf", ans);
	return 0;
}
