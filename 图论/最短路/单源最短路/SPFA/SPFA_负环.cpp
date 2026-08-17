#include<bits/stdc++.h>
#define inf 0x3f3f3f3f

using namespace std;

int t, n, m ,s = 1;
vector<vector<pair<int, int>>> gra;
vector<int> dist, cnt;
vector<bool> vis;

bool spfa(){
	dist.assign(n + 5, inf);
	vis.assign(n + 5, 0);
	cnt.assign(n + 5, 0);
	queue<int> q;
	dist[s] = 0;
	vis[s] = 1;
	q.push(s);
	cnt[s] = 1;
	while(!q.empty()){
		int u = q.front();
		vis[u] = 0;
		q.pop();
		for(auto x : gra[u]){
			if(dist[x.first] > dist[u] + x.second){
				dist[x.first] = dist[u] + x.second;
				if(vis[x.first] != 1){
					vis[x.first] = 1;
					q.push(x.first);
					cnt[x.first]++;
					if(cnt[x.first] > n){
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int main(){
	cin>>t;
	while(t--){
		cin>>n>>m;
		gra.resize(n + 5);
		gra.clear();
		dist.resize(n + 5);
		cnt.resize(n + 5);
		vis.resize(n + 5);
		for(int i = 0;i < m;i++){
			int u, v, w;
			cin>>u>>v>>w;
			if(w >= 0){
				gra[u].push_back({v, w});
				gra[v].push_back({u, w});
			}
			else{
				gra[u].push_back({v, w});
			}
		}
		if(spfa() == 1){
			cout<<"YES\n";
		}
		else{
			cout<<"NO\n";
		}
	}
	return 0;
}