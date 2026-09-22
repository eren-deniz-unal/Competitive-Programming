#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN

void solve(){
    ll n, w;
    cin>>n>>w;

    ll weights[n + 1];
    ll vals[n + 1];
    ll dp[n + 1][w + 1]; // dp[i][j] => i -> current item, j -> weight after decision
    for(int i = 1 ; i <= n ; i++){
        cin>>weights[i]>>vals[i];
    }
    for(int i = 0 ; i <= w ; i++){
        dp[0][i] = 0;
    }

    for(int i = 1 ; i <= n ; i++){
        for(int j = 0 ; j <= w ; j++){
            //dont take i -> dp[i - 1][j], take i -> dp[i - 1][j - w[i]] + v[i]
            //dp[i - 1][j - w[i]] -> max val of the weight that i need to be to get to the current weight after taking i
            dp[i][j] = dp[i - 1][j];
            if(j >= weights[i]) dp[i][j] = max(dp[i][j], dp[i - 1][j - weights[i]] + vals[i]);
        }
    }

    ll ans = 0;
    for(int i = 0 ; i <= w ; i++){
        ans = max(ans, dp[n][i]);
    }
    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
