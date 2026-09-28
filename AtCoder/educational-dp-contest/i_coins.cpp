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
    long double prob[n + 1];
    for(int i = 1 ; i <= n ; i++){
        cin>>prob[i];
    }

    long double dp[n + 1][n + 1]; //dp[i][j] => i -> cur coin, j -> head count until now
    for(int i = 0 ; i <= n ; i++){
        dp[0][i] = 0;
        dp[i][0] = 1;
    }

    for(int i = 1 ; i <= n ; i++){
        for(int j = 1 ; j <= n ; j++){
            dp[i][j] = (dp[i - 1][j - 1] * prob[i]) + (dp[i - 1][j] * (1 - prob[i])); // if i get heads + if i get tails
        }
    }

    cout<<setprecision(numeric_limits<double>::max_digits10); //<- did not know this
    cout<<dp[n][(n + 1) / 2];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    solve();

    return 0;
}
