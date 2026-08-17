#include<bits/stdc++.h>
#define inf INT_MAX

using namespace std;

int n, m, s;
vector<vector<pair<int, int>>> gra;
vector<int> dist;
vector<bool> vis;

void dijkstra(){
	dist[s] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push({0, s});
	while(!q.empty()){
		int u = q.top().second;
		q.pop();
		if(vis[u] == 1){
			continue;
		}
		vis[u] = 1;
		for(auto x : gra[u]){
			int v = x.first, w = x.second;
			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				q.push({dist[v], v});
			}
		}
	}
}

int main(){
	cin>>n>>m>>s;
	gra.resize(n + 5);
	dist.resize(n + 5);
	dist.assign(n + 5, inf);
	vis.resize(n + 5);
	for(int i = 0;i < m;i++){
		int u, v, w;
		cin>>u>>v>>w;
		gra[u].push_back({v, w});
	}
	dijkstra();
	for(int i = 1;i <= n;i++){
		cout<<dist[i]<<" ";
	}
}