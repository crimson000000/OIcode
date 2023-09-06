#include<bits/stdc++.h>
using namespace std;
const int N=200+10;
int d[N][N],t[N];
int n,m;


void floyd(int k){
    
    for (int i = 0; i < n; i ++ ){
		for (int j = 0; j < n; j ++ ){
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		}
		
	}
}


int main(){
	memset(d,0x3f,sizeof d);
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",&t[i]);
		d[i][i]=0;
	}
	
	for(int i=0;i<m;i++){
		int a,b,w;
		scanf("%d%d%d",&a,&b,&w);
		d[a][b]=d[b][a]=w;
	}
	

	int q;
	scanf("%d",&q);
	int now=0;
	for(int i=0;i<q;i++){
		int x,y,ti;
		scanf("%d%d%d",&x,&y,&ti);
		while(t[now] <= ti && now<n){
			floyd(now);
			now++;
		}
		if(t[x] > ti || t[y] > ti) cout<<-1<<endl;
		else if(d[x][y]>0x3f3f3f1f) cout<<-1<<endl;
		else cout<<d[x][y]<<endl;
	}
}
