#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN

void solve(){
    ll n;
    cin>>n;

    ll a[n];
    ll b[n];
    ll c[n];
    ll dp[n][3]; // dp[n][0] -> do a, dp[n][1] -> do b, dp[n][2] -> do c

    for(int i = 0 ; i < n ; i++){
        cin>>a[i]>>b[i]>>c[i];
        dp[i][0] = -1;
        dp[i][1] = -1;
        dp[i][2] = -1;
    }
    dp[0][0] = a[0];
    dp[0][1] = b[0];
    dp[0][2] = c[0];

    for(int i = 1 ; i < n ; i++){
        dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + a[i];
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + b[i];
        dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]) + c[i];
    }

    cout<<max(max(dp[n - 1][0], dp[n - 1][1]), dp[n - 1][2]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    solve();

    return 0;
}
