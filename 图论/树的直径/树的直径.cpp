#include<bits/stdc++.h>

using namespace std;

int n, s = 0;
vector<vector<int>> tr;
vector<int> dist;

void dfs(int u, int fa){
	for(auto v : tr[u]){
		if(v == fa){
			continue;
		}
		dist[v] = dist[u] + 1;
		if(dist[v] > dist[s]){
			s = v;
		}
		dfs(v, u);
	}
}

int main(){
	cin>>n;
	tr.resize(n + 5);
	dist.resize(n + 5);
	for(int i = 0;i < n - 1;i++){
		int u, v;
		cin>>u>>v;
		tr[u].push_back(v);
		tr[v].push_back(u);
	}
	dfs(1, 0);
  	dist[s] = 0, dfs(s, 0);
	cout<<dist[s];
}