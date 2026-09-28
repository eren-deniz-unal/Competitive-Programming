#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n, m;
    cin>>n>>m;
    char arr[n + 1][m + 1];
    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            cin>>arr[i][j];
        }
    }

    ll dp[n + 1][m + 1];
    for(int i = 0 ; i <= n ; i++){
        dp[i][0] = 0;
    }
    for(int i = 1 ; i <= m ; i++){
        dp[0][i] = 0;
    }
    dp[1][1] = 1;

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= m ; j++){
            if(i == 1 && j == 1) continue;
            if(arr[i][j] == '#') dp[i][j] = 0;
            else dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            if(dp[i][j] > mod) dp[i][j] -= mod;
        }
    }

    cout<<dp[n][m];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}