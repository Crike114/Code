#include<bits/stdc++.h>
using namespace std;

int n, m;
vector<int> a;
vector<vector<int>> dp;

void init(int logn){
    for(int i = 0;i < n;i++){
        dp[i][0] = a[i];
    }
    for(int j = 1;j <= logn;j++){
        for(int i = 0;i + (1 << j) <= n;i++){
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(0);
    cout.tie(nullptr)->sync_with_stdio(0);
    cin>>n>>m;
    a.resize(n);
    dp.resize(n);
    int logn = __lg(n);
    for(int i = 0;i < n;i++){
        dp[i].resize(logn + 1);
        cin>>a[i];
    }

    init(logn);

    for(int i = 0;i < m;i++){
        int l, r;
        cin>>l>>r;
        l--, r--;
        int k = __lg(r - l + 1);
        cout<<max(dp[l][k], dp[r - (1 << k) + 1][k])<<"\n";
    }
}