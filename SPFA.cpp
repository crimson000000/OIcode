#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int h[N],e[N],ne[N],w[N],idx;
int dist[N];
bool st[N];


void add(int a,int b,int c){
	e[idx]=b,w[idx]=c,ne[idx]=h[a],h[a]=idx++;
}

void SPFA(int s){
	memset(dist , 0x3f,sizeof dist);
	dist[s] = 0;
	
	queue<int> q;
	q.push(s);
	st[s] = true;
	
	while(q.size()){
		int t = q.front();
		q.pop();
		st[t] = false;
		
		for(int i=h[t];i!=-1;i=ne[i]){
			int j=e[i];
			
			if(dist[j] > dist[t] + w[i]){
				dist[j] = dist[t] + w[i];
				if(!st[j]){
					q.push(j);
					st[j] = true;
				}
			}
		}
	}
}

int main(){
	int n,m,s;
	memset(h,-1,sizeof h);
	scanf("%d%d%d",&n,&m,&s);
	for(int i=0;i<m;i++){
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
	}
	
	SPFA(s);
	
	for(int i=1;i<=n;i++){
		if(dist[i]==0x3f3f3f3f) cout<<2147483647<<" ";
		else cout<<dist[i]<<" ";
	}
}
