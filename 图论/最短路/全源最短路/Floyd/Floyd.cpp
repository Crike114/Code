#include<bits/stdc++.h>
#define inf 0x3f3f3f3f

using namespace std;

int n, m;
int a[105][105];

int main(){
	cin>>n>>m;
	memset(a, 0x3f, sizeof(a));
	for(int i = 1;i <= n;i++){
		a[i][i] = 0;
	}
	for(int i = 0;i < m;i++){
		int u, v, w;
		cin>>u>>v>>w;
		a[u][v] = min(a[u][v], w);
		a[v][u] = min(a[v][u], w);
	}
	for(int k = 1;k <= n;k++){
		for(int i = 1;i <= n;i++){
			for(int j = 1;j <= n;j++){
				a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
			}
		}
	}
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= n;j++){
			cout<<a[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}