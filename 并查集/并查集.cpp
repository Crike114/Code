#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<int> parent;

int find(int x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}
int unionset(int x, int y){
    int xp = find(x);
    int yp = find(y);
    if(xp != yp){
        parent[yp] = xp;
        return 1;
    }
    return 0;
}
int init(int n){
    for(int i = 1;i <= n;i++){
        parent[i] = i;
    }
    return 0;
}

int main(){
    cin>>n>>m;
    parent.resize(n + 1);
    init(n + 1);
    for(int i = 1;i <= m;i++){
        int z, a, b;
        cin>>z>>a>>b;
        if(z == 1){
            unionset(a, b);
        }
        else if(z == 2){
            if(find(a) == find(b)){
                cout<<"Y\n";
            }
            else{
                cout<<"N\n";
            }
        }
    }
    return 0;
}