#include <bits/stdc++.h>
using namespace std;
const int N = 30;
bool d[N][N];
int f[N], pre[N];
int a[N];
int n, ed;
int ans = 0;

void print(int x){
	if(pre[x] == 0) {
		cout << x << " ";
		return;
	}
	print(pre[x]);
	cout << x << " ";
}

int main(){
	scanf("%d", &n);
	
	for(int i = 1; i <= n; i ++ ){
		scanf("%d", &a[i]);
		f[i] = a[i];
	} 
	
	for(int i = 1; i <= n; i ++ ){
		for(int j = i + 1; j <= n; j ++ ){
			cin >> d[i][j];
		}
	}
	
	for(int i = 1; i <= n; i ++ ){
		for(int j = 1; j <= i; j ++ ){
			if(d[j][i] && f[j] + a[i] > f[i]){
				f[i] = f[j] + a[i];
				pre[i] = j;
			}
		}
		if(f[i] > ans){
			ed = i;
			ans = f[i];
		}
	}
	
	
	for(int i = 1; i <= n; i ++ ) ans = max(ans, f[i]);
	
	print(ed);
	puts("");
	cout << ans << endl;
	return 0;
} 
