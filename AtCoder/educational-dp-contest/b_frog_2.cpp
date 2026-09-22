#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN

void solve(){
    ll n, k;
    cin>>n>>k;

    ll h[n];
    ll dp[n];
    for(int i = 0 ; i < n ; i++){
        cin>>h[i];
        dp[i] = LLMAX;
    }
    dp[0] = 0;

    for(int i = 0 ; i < n ; i++){
        for(int j = i + 1 ; j <= i + k ; j++){
            if(j >= n) break;
            dp[j] = min(abs(h[i] - h[j]) + dp[i], dp[j]);
        }
    }

    cout<<dp[n - 1];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
