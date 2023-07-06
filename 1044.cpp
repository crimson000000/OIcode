#include<bits/stdc++.h>
using namespace std;
const int N = 40;
long long c[N][N];
int n;

int main(){
	for(int i = 0 ; i < N ;i ++) c[i][i] = c[i][0] = 1;
		
	
	scanf("%d", &n);

	for(int i = 1 ; i <= N ; i ++){
		for(int j = 1 ; j < i ; j ++)
			c[i][j] = c[i-1][j] + c[i-1][j-1];  
	}
	cout<<c[2*n][n]-c[2*n][n-1]<<endl;
}
