#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN

void solve(){
    ll n, w;
    cin>>n>>w;

    ll vals[n + 1];
    ll weights[n + 1];
    ll tVal = 0;
    for(int i = 1 ; i <= n ; i++){
        cin>>weights[i]>>vals[i];
        tVal += vals[i];
    }

    ll dp[n + 1][tVal + 1]; //dp[i][j] => i -> cur item, j -> cur val , dp[i][j] -> whats the least weight to get to this value
    for(int i = 0 ; i <= tVal ; i++){
        dp[0][i] = LLMAX;
    }
    dp[0][0] = 0;

    ll maxVal = 0;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 0 ; j <= tVal ; j++){
            dp[i][j] = dp[i - 1][j]; //dont take cur item
            if(j >= vals[i] && dp[i - 1][j - vals[i]] != LLMAX) dp[i][j] = min(dp[i][j], dp[i - 1][j - vals[i]] + weights[i]); //take cur item
            if(dp[i][j] <= w && j > maxVal) maxVal = j;
        }
    }

    cout<<maxVal;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
