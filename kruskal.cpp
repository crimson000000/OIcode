#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=1e6+10;

int p[N]; 
int find(int x){
	if(p[x] != x) p[x]=find(p[x]);
	return p[x];
}

struct edge{
	int a,b,w;
	bool operator< (const edge &W) const{
		return w<W.w;
	}
}edges[N];

int kruskal(){
	sort(edges, edges + m);
	
	int res = 0, cnt = 0;
	
	for(int i = 0; i < m; i ++){
		int a = edges[i].a, b = edges[i].b, w = edges[i].w;
		
		a = find(a),b = find(b);
		
		if(a != b){
			res += w;
			cnt ++;
			p[a] = b;
		}
	}
	
	if(cnt < n-1) return 1145141919;
	else return res;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) p[i]=i;
	for(int i=0;i<m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		edges[i]={a,b,c};
	}
	
	
	
	int t=kruskal();
	
	if(t == 1145141919) cout<<"orz"<<endl;
	else cout<<t<<endl;
}
