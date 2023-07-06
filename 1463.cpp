#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int a[] = {2,3,5,7,11,13,17,19,23,29};
int minx, sum;
int n;

void dfs(int u, int last, int p, int s){
	if(s > sum || s == sum && p < minx){
		sum = s;
		minx = p;
	}
	
	for(int i = 1; i <= last; i ++ ){
		if((ll)p * a[u] > n) break;
		p *= a[u];
		dfs(u + 1, i, p, s * (i + 1));
	}
}

int main(){
	cin >> n;
	
	dfs(0, 30, 1, 1);
	cout << minx << endl;
	
	return 0;
}
