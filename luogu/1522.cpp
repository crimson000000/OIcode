#include<bits/stdc++.h>
using namespace std;
const int N=150+10;
double INF=1145141919.810;
int n;

double dist[N][N],diameter[N];
int p[N];

struct area{
	int x, y;
}areas[N];

double di(const area& a,const area& b){
	return sqrt( (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y) );
}

int find(int x){
	if(p[x] != x) p[x] =find(p[x]);
	return p[x];
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&areas[i].x,&areas[i].y);
		p[i]=i;
	}
	for(int i=0;i<n;i++){
		char s[N];
		scanf("%s",s);
		for(int j=0;j<n;j++){
			if(s[j] == '1' || i == j){
				dist[i][j] = di(areas[i],areas[j]);	
				p[find(i)]=find(j);
			} 
			else dist[i][j] =INF;
		}
	}
	
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
	
	double sp[N];
	for(int i=0;i<n;i++){
		sp[i]=0.0;
		
		for(int j=0;j<n;j++){
			if(dist[i][j]<INF){
				sp[i]=max(sp[i],dist[i][j]);
			}
		}
		diameter[find(i)] = max(diameter[find(i)],sp[i]);
	}
	
	double mn=INF,mx;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(find(i) != find(j)){
				mx=max(max(diameter[find(i)],diameter[find(j)]),sp[i]+di(areas[i],areas[j])+sp[j]);
				mn=min(mx,mn);
			}
		}
	}
	
	printf("%.6f",mn);
	return 0;
}
