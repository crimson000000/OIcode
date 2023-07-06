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

double di(area& a,area& b){
	return sqrt( (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y) );
}

void dfs(int i, int id)
{
    p[i] = id;
    for (int j = 0; j < n; ++j)
        if (!p[j] && dist[i][j] < INF)
            dfs(j, id);
}

int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&areas[i].x,&areas[i].y);
		
	}
	for(int i=0;i<n;i++){
		char s[N];
		scanf("%s",s);
		for(int j=0;j<n;j++){
			if(s[j] == '1' || i == j){
				dist[i][j] = di(areas[i],areas[j]);	
			} 
			else dist[i][j] =INF;
		}
	}
	
	int id = 0;
    for (int i = 0; i < n; ++i)
        if (!p[i])
            dfs(i, ++id);
	
	for(int k=0;k<n;k++){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]); 
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
		
	}
	
	double mn=INF,mx;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(p[i] != p[j]){
				mx=max(max(diameter[p[i]],diameter[p[j]]),sp[i]+di(areas[i],areas[j])+sp[j]);
				mn=min(mx,mn);
			}
		}
	}
	
	printf("%.6f",&mn);
	return 0;
}
