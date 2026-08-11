#include<bits/stdc++.h>
#define int long long
using namespace std;

int n, m;
vector<int> a, d;

void init(int l, int r, int p){
    if(l == r){
        d[p] = a[l];
        return;
    }
    int m = l + ((r - l) >> 1);
    init(l, m, p * 2), init(m + 1, r, p * 2 + 1);
    d[p] = d[p * 2] + d[(p * 2) + 1];
}
void update(int s, int t, int p, int x, int v){
    if(s == t){
        d[p] += v;
        return;
    }
    int mid = s + ((t - s) >> 1);
    if(x <= mid){
        update(s, mid, p * 2, x, v);
    }
    else{
        update(mid + 1, t, p * 2 + 1, x, v);
    }
    d[p] = d[p * 2] + d[p * 2 + 1];
}
int find(int l, int r, int s, int t, int p){
    if(l <= s && t <= r){
        return d[p];
    }
    int m = s + ((t - s) >> 1), sum = 0;
    if(l <= m){
        sum += find(l, r, s, m, p * 2);
    }
    if(r > m){
        sum += find(l, r, m + 1, t, p * 2 + 1);
    }
    return sum;
}

signed main(){
    cin>>n>>m;
    a.resize(n + 1);
    d.resize(4 * n + 1);
    for(int i = 1;i <= n;i++){
        cin>>a[i];
    }
    init(1, n, 1);
    for(int i = 1;i <= m;i++){
        int x, y, z;
        cin>>x>>y>>z;
        if(x == 1){
            update(1, n, 1, y, z);
        }
        else if(x == 2){
            cout<<find(y, z, 1, n, 1)<<"\n";
        }
    }
}