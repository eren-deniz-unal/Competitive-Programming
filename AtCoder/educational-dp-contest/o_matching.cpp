#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LLONG_MAX
#define LLMIN LLONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n;
    cin>>n;
    ll arr[n][n];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cin>>arr[i][j];
        }
    }

    ll dp[(1<<n)];
    for(int i = 0 ; i < (1<<n) ; i++) dp[i] = 0;
    dp[0] = 1;

    for(int mask = 0 ; mask < (1<<n) ; mask++){
        ll boyIndex = __builtin_popcount(mask);
        for(int girl = 0 ; girl < n ; girl++){
            if(arr[boyIndex][girl] && !(mask&(1<<girl))){
                (dp[mask^(1<<girl)] += dp[mask]) %= mod;
            }
        }
    }

    cout<<dp[(1<<n) - 1];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(numeric_limits<double>::max_digits10); // set cout to print up to 10 digits of precision

    solve();

    return 0;
}
