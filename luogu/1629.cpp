#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
typedef pair<int,int> PII;
int h[N],e[N],ne[N],w[N],idx;
int dist[N];
bool st[N];
int m,n;

void add(int a,int b,int c){
	e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}

void dijkstra(int s){
	memset(dist,0x3f,sizeof dist);
	dist[s]=0;
	memset(st,0,sizeof st);
	
	priority_queue<PII,vector<PII>,greater<PII>> heap;
	heap.push({0,s});
	
	while(!heap.empty()){
		auto t=heap.top();
		heap.pop();
		int distance=t.first,ver=t.second;
		
		if(st[ver]) continue;
		
		st[ver]=true;
		for(int i=h[ver];i!=-1;i=ne[i]){
			int j=e[i];
			if(dist[j]> distance +w[i]){
				dist[j] = distance +w[i];
				heap.push({dist[j],j});
			}
		}
	}
}


int main(){
	memset(h,-1,sizeof h);
	scanf("%d%d",&m,&n);
	
	for(int i=0;i<n;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b+m,a+m,c);
	}
	
	dijkstra(1);
	
	int ans=0;
	for(int i=2;i<=m;++i){
		ans+=dist[i];
	}
	
	dijkstra(m+1);
	for(int i=2+m;i<=m<<1;++i){
		ans+=dist[i];
	}
	cout<<ans<<endl;
}
