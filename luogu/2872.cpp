#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=1e3+10;
int x[N],y[N];
struct edge{
	int a,b;
	double w;
	
	bool operator < (const edge& W){
		return w<W.w;
	}
}edges[N],iedges[N];

double dis(int a,int b){
	return sqrt(  (x[a]-x[b])*(x[a]-x[b])+(y[a]-y[b])*(y[a]-y[b])   );
}

int p[N];

int find(int x){
	if(x != p[x]) p[x]=find(p[x]);
	return p[x];
}

double kruskal(){
	for(int i=1;i<=n;i++) p[i]=i;
	sort(edges,edges+m);
	
	int cnt=0;
	double res=0;
	for(int i=0;i<m;i++){
		int a=edges[i].a,b=edges[i].b;
		double w=edges[i].w;
		
		 a=find(a),b=find(b);
		if(a != b){
			cnt++;
			res+=w;
			p[a]=b;
		}
	}
	
	if(cnt<n-1) return 1145141919;
	else return res;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d%d",&x[i],&y[i]);
	}
	int cnt=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(i==j) edges[cnt++] = {i,j,0};
			else edges[cnt++] = {i,j,dis(i,j)};
	for(int i=0;i<m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		iedges[i]={a,b,dis(a,b)};
	}
	
	auto t=kruskal();
	
	cout<<fixed<<setprecision(2)<<t<<endl;
}
