#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll dp[105][int(1e5) + 5];
ll dpPreSum[105][int(1e5) + 5];

void solve(){
    ll n, k;
    cin>>n>>k;
    ll arr[n + 1];
    for(int i = 1 ; i <= n ; i++){
        cin>>arr[i];
        dp[i][0] = 1;
        dpPreSum[i][0] = 1;
    }
    if(k == 0){
        cout<<1;
        return;
    }
    for(int i = 1 ; i <= k ; i++){
        dp[0][i] = 0;
        dpPreSum[0][i] = 1;
    }
    dp[0][0] = 1;
    dpPreSum[0][0] = 1;

    ll ans = 0;
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= k ; j++){
            dp[i][j] = dpPreSum[i - 1][j] - (arr[i] < j ? dpPreSum[i - 1][j - arr[i] - 1] : 0);
            while(dp[i][j] < 0) dp[i][j] += mod;
            dp[i][j] %= mod;
            dpPreSum[i][j] = (dpPreSum[i][j - 1] + dp[i][j]) % mod;
        }
    }
    cout<<dp[n][k];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(numeric_limits<double>::max_digits10); // set cout to print up to 10 digits of precision

    solve();

    return 0;
}
