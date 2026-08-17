#include<bits/stdc++.h>
#define inf INT_MAX
#define mod 100003

using namespace std;

int n, m;
vector<vector<pair<int, int>>> gra;
vector<int> dist, ans;
vector<bool> vis;

void dijkstra(){
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	dist[1] = 0;
	q.push({0, 1});
	while(!q.empty()){
		int u = q.top().second, d = q.top().first;
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
				ans[v] = ans[u];
			}
			else if(dist[v] == dist[u] + w){
				ans[v] += ans[u];
				ans[v] = ans[v] % mod;
			}
		}
	}
}

int main(){
	cin>>n>>m;
	gra.resize(n + 5);
	dist.resize(n + 5);
	ans.resize(n + 5);
	vis.resize(n + 5);
	dist.assign(n + 5, inf);
	ans[1] = 1;
	for(int i = 0;i < m;i++){
		int x, y;
		cin>>x>>y;
		gra[x].push_back({y, 1});
		gra[y].push_back({x, 1});
	}
	dijkstra();
	for(int i = 1;i <= n;i++){
		cout<<ans[i]<<"\n";
	}
}