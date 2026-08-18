#include<bits/stdc++.h>

using namespace std;

int n;
vector<vector<int>> tr;
vector<int> in;

int main(){
    cin>>n;
    tr.resize(n + 5);
    in.resize(n + 5);
    for(int i = 1;i <= n;i++){
        while(1){
            int x;
            cin>>x;
            if(x == 0){
                break;
            }
            tr[i].push_back(x);
            in[x]++;
        }
    }
    queue<int> q;
    for(int i = 1;i <= n;i++){
        if(in[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u = q.front();
        q.pop();
        cout<<u<<" ";
        for(auto v : tr[u]){
            in[v]--;
            if(in[v] == 0){
                q.push(v);
            }
        }
    }
    return 0;
}