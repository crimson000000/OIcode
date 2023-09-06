#include <bits/stdc++.h>
using namespace std;
char ch;
int fx, fy;
const int dx[] = {0, 1, 0, -1, 0};
const int dy[] = {0, 0, -1, 0, 1};

struct matrix {
  	int a[5][5];

  	bool operator<(matrix x) const {
    	for (int i = 1; i <= 3; i++)
   		  	for (int j = 1; j <= 3; j++)
        		if (a[i][j] != x.a[i][j]) return a[i][j] < x.a[i][j];
    	return false;
  	}		
};
matrix st, f;

int h(matrix x){
	int sum = 0;
	for(int i = 1; i <= 3; i ++ ){
		for(int j = 1; j <= 3; j ++ ){
			if(x.a[i][j] != st.a[i][j]) sum ++;
		}
	}
	return sum;
}

struct node{
	matrix a;
	int t;
	bool operator < (node x) const{
		return t + h(a) > x.t + h(x.a);
	}
};

set<matrix> vis;
priority_queue<node> q;


int main(){
	
	st.a[1][1] = 1; 
	st.a[1][2] = 2;
	st.a[1][3] = 3;
	st.a[2][1] = 8;
	st.a[2][2] = 0;
	st.a[2][3] = 4;
	st.a[3][1] = 7;
	st.a[3][2] = 6;
	st.a[3][3] = 5;
	
	for(int i = 1; i <= 3; i ++ ){
		for(int j = 1; j <= 3; j ++ ){
			scanf("%c", &ch);
			f.a[i][j] = ch - '0';
		}
	}
	
	q.push({f, 0});
	
	while(!q.empty()){
		auto t = q.top();
		q.pop();
		if(!h(t.a)){
			cout << t.t << endl;
			return 0;
		}
		
		for(int i = 1; i <= 3; i ++ ){
			for(int j = 1; j <= 3; j ++ ){
				if(!t.a.a[i][j]) fx = i, fy = j;
			}
		}
		
		for(int i = 0; i < 5; i ++ ){
			int xx = fx + dx[i], yy = fy + dy[i];
			if(xx > 0 && xx <= 3 && yy > 0 && yy <= 3){
				swap(t.a.a[xx][yy], t.a.a[fx][fy]);
				if(!vis.count(t.a)){
					vis.insert(t.a);
					q.push({t.a, t.t + 1});
				}
				
				swap(t.a.a[xx][yy], t.a.a[fx][fy]);
				
			}
		}
	}	
	return 0;
}
