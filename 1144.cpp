#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10,M=100003;
typedef pair<int,int> PII;
int h[N],e[N],ne[N],idx;
int n,m;
int cnt[N],dist[N];
bool st[N];

void add(int a,int b){
	e[idx]=b,ne[idx]=h[a],h[a]=idx++;
}

void dijkstra(){
	memset(dist,0x3f,sizeof dist);
	dist[1]=0;
	cnt[1]=1;
	
	priority_queue<PII,vector<PII>,greater<PII>> heap;
	heap.push({0,1});
	
	while(!heap.empty()){
		auto t=heap.top();
		heap.pop();
		int distance=t.first,ver=t.second;
		
		if(st[ver]) continue;
		st[ver]=true;
		
		for(int i=h[ver];i!=-1;i=ne[i]){
			int j=e[i];
			
			if(dist[j]>distance+1){
				dist[j]=distance+1;
				cnt[j]=cnt[ver];
				heap.push({dist[j],j});
			}else if(dist[j] == distance+1){
				cnt[j]+=cnt[ver];
				cnt[j]%=M;
			}
		}
	}
	
}

int main(){
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof h);
	for(int i=0;i<m;i++){
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	
	dijkstra();
	
	for(int i=1;i<=n;i++) cout<<cnt[i]<<endl;
}
