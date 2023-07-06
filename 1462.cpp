#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10,M=1e9+10;
typedef pair<int,int> PII;
int h[N],w[N],e[N],ne[N],idx;
int n,m,b;
int money[N],dist[N];
bool st[N];

void add(int a,int b,int c){
	e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}

bool dijkstra(int x){
	if(x<money[1]) return 0;
	memset(dist,0x3f,sizeof dist);
	dist[1]=0;
	memset(st,0,sizeof st);
	
	priority_queue<PII,vector<PII>,greater<PII>> heap;
	heap.push({0,1});
	
	
	while(!heap.empty()){
		auto t=heap.top();
		heap.pop();
		int distance=t.first,ver=t.second;
		
		if(st[ver])continue;
		st[ver]=true;
		
		for(int i=h[ver];i!=-1;i=ne[i]){
			int j=e[i];
			if(dist[j]>distance+w[i] && money[j]<=x && st[j]== 0){
				dist[j]=distance+w[i];
				heap.push({dist[j],j});
			}
		}
	}
	if(dist[n]>b) return 0;
	else return 1;
}

int main(){
	memset(h,-1,sizeof h);
	scanf("%d%d%d",&n,&m,&b);
	
	for(int i=1;i<=n;i++){
		scanf("%d",&money[i]);
	}
	
	for(int i=1;i<=m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);add(b,a,c);
	}
	
	if(!dijkstra(M)){
		cout<<"AFK"<<endl;
		return 0;
	}
	
	int l=1,r=M;
	while(l<=r){
		int mid=l+r>>1;
		if(dijkstra(mid)) r=mid-1;
		else l=mid+1;
	}
	
	cout<<l<<endl;
} 
