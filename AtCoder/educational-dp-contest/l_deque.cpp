#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n;
    cin>>n;
    ll arr[n + 1];
    ll dpP1[n + 1][n + 1]; //dp[l][r] => l -> left, r -> right, dp[l][r] -> best score if my move
    ll dpP2[n + 1][n + 1];
    for(int i = 1 ; i <= n ; i++){
        cin>>arr[i];
        dpP1[i][0] = 0;
        dpP1[0][i] = 0;
        dpP1[i][i] = arr[i];
        dpP2[i][0] = 0;
        dpP2[0][i] = 0;
        dpP2[i][i] = -arr[i];
    }
    dpP1[0][0] = 0;
    dpP2[0][0] = 0;

    for(int rangeSize = 2 ; rangeSize <= n ; rangeSize++){
        for(int l = 1 ; l <= n ; l++){
            if(l + rangeSize - 1 > n) break;
            ll r = l + rangeSize - 1;
            dpP1[l][r] = max(dpP2[l + 1][r] + arr[l], dpP2[l][r - 1] + arr[r]);
            dpP2[l][r] = min(dpP1[l + 1][r] - arr[l], dpP1[l][r - 1] - arr[r]);
        }
    }
    cout<<dpP1[1][n];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(numeric_limits<double>::max_digits10); // set cout to print up to 10 digits of precision

    solve();

    return 0;
}
