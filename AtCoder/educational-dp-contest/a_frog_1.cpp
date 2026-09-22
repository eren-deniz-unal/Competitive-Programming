#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN

void solve(){
    ll n;
    cin>>n;
    ll h[n];
    for(int i = 0 ; i < n ; i++){
        cin>>h[i];
    }

    ll dp[n];
    for(int i = 0 ; i < n ; i++) dp[i] = LLMAX;
    dp[0] = 0;
    for(int i = 0 ; i < n ; i++){
        dp[i + 1] = min(abs(h[i] - h[i + 1]) + dp[i], dp[i + 1]);
        dp[i + 2] = min(abs(h[i] - h[i + 2]) + dp[i], dp[i + 2]);
    }
    cout<<dp[n - 1];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
