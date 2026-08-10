#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> a;
vector<vector<int>> dp;

int gcd(int a,int b) {
    return b > 0 ? gcd(b, a % b) : a;
}
void init(int logn){
    for(int i = 0;i < n;i++){
        dp[i][0] = a[i];
    }
    for(int j = 1;j <= logn;j++){
        for(int i = 0;i + (1 << j) <= n;i++){
            dp[i][j] = gcd(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}
bool check(int l, int r) {
    int len = r - l + 1;
    int k = __lg(len);
    int g = gcd(dp[l][k], dp[r - (1 << k) + 1][k]);
    return g == 1;
}

// int query(int l, int r) {
//     int k = lg[r - l + 1];
//     return gcd(st[l][k], st[r - (1<<k) + 1][k]);
// }
// int main(){
//     cin.tie(nullptr)->sync_with_stdio(0);
//     cout.tie(nullptr)->sync_with_stdio(0);
//     cin>>n;
//     a.resize(n);
//     dp.resize(n);
//     int logn = __lg(n);
//     for(int i = 0;i < n;i++){
//         dp[i].resize(logn + 1);
//         cin>>a[i];
//     }

//     init(logn);

//     int l = 1, r = n;
//     int k = __lg(r - l + 1);
//     cout<<max(dp[l][k], dp[r - (1 << k) + 1][k])<<"\n";

// }

int main(){
    cin.tie(nullptr)->sync_with_stdio(0);
    cout.tie(nullptr)->sync_with_stdio(0);
    cin>>n;
    int cnt1 = 0;
    int logn = __lg(n);
    int ans = INT_MAX;
    a.resize(n);
    dp.resize(n);
    for(int i = 0;i < n;i++){
        dp[i].resize(logn + 1);
        cin>>a[i];
        if(a[i] == 1){
            cnt1++;
        }
    }

    if(cnt1 > 0){
        cout<<n - cnt1<<'\n';
        return 0;
    }

    init(logn);
    for(int l = 0;l < n;l++){
        int low = l, high = n - 1, bans = -1;

        while(low <= high){
            int mid = (low + high) / 2;

            if(check(l, mid) == 1){
                bans = mid;
                high = mid - 1;
            }
            else{
                low = mid + 1;
            }
        }
        if(bans != -1){
            ans = min(ans, (bans - l) + (n - 1));
        }
    }

    if(ans == INT_MAX){
        cout<<-1<<'\n';
    }
    else{
        cout<<ans<<'\n';
    }
    return 0;
}