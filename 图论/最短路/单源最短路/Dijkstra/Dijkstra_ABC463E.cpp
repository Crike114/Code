#include<bits/stdc++.h>
#define int long long
#define inf (LLONG_MAX >> 1)

using namespace std;

int n, m, y, s = 1;
vector<vector<pair<int, int>>> gra;
vector<int> dist, tim;
vector<bool> vis;

void dijkstra(){
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	dist.assign(n + 5, inf);
	vis.assign(n + 5, 0);
	dist[s] = 0;
	q.push({dist[s], s});
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

signed main(){
	cin>>n>>m>>y;
	gra.resize(n + 5);
	dist.resize(n + 5);
	vis.resize(n + 5);
	tim.resize(n + 5);
	for(int i = 0;i < m;i++){
		int u, v, t;
		cin>>u>>v>>t;
		gra[u].push_back({v, t});
		gra[v].push_back({u, t});
	}
	for(int i = 1;i <= n;i++){
		cin>>tim[i];
	}
	for(int i = 1;i <= n;i++){
		gra[i].push_back({0, tim[i]});
		gra[0].push_back({i, tim[i] + y});
	}
	dijkstra();
	for(int i = 2;i <= n;i++){
		cout<<dist[i]<<" ";
	}
	return 0;
}