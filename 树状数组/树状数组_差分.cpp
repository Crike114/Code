#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<long long> bit;

int lowbit(int x){
    return x & -x;
}
void add(int idx, long long val){
    while(idx <= n){
        bit[idx] += val;
        idx += lowbit(idx);
    }
}
long long sum(int idx){
    long long res = 0;
    while(idx > 0){
        res += bit[idx];
        idx -= lowbit(idx);
    }
    return res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin>>n>>m;
    bit.resize(n);
    long long last = 0, cur;
    for(int i = 1;i <= n;i++){
        cin>>cur;
        add(i, cur - last);
        last = cur;
    }

    while(m--){
        int op;
        cin>>op;
        if(op == 1){
            int l, r;
            long long k;
            cin>>l>>r>>k;
            add(l, k);
            if(r + 1 <= n){
                add(r + 1, -k);
            }
        }
        else{
            int x;
            cin>>x;
            cout<<sum(x)<<"\n";
        }
    }
}