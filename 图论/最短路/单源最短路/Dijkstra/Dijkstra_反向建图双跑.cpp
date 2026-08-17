#include<bits/stdc++.h>
#define inf INT_MAX

using namespace std;

int n, m, x;
vector<vector<pair<int, int>>> gra, neggra;
vector<int> dist, dist1;
vector<bool> vis;

void dijkstra(vector<vector<pair<int, int>>> gra){
	dist.assign(n + 5, inf);
	vis.assign(n + 5, 0);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	dist[x] = 0;
	q.push({0, x});
	while(!q.empty()){
		int u = q.top().second;
		q.pop();
		if(vis[u] == 1){
			continue;
		}
		vis[u] = 1;
		for(auto _x : gra[u]){
			int v = _x.first, w = _x.second;
			if(dist[v] > dist[u] + w){
				dist[v] = dist[u] + w;
				q.push({dist[v], v});
			}
		}
	}
}

int main(){
	cin>>n>>m>>x;
	dist.resize(n + 5);
	vis.resize(n + 5);
	gra.resize(n + 5);
	neggra.resize(n + 5);
	for(int i = 0;i < m;i++){
		int u, v, w;
		cin>>u>>v>>w;
		gra[u].push_back({v, w});
		neggra[v].push_back({u, w});
	}
	dijkstra(gra);
	dist1 = dist;
	dijkstra(neggra);
	int ans;
	for(int i = 1;i <= n;i++){
		ans = max(ans, dist1[i] + dist[i]);
	}
	cout<<ans;
	return 0;
}