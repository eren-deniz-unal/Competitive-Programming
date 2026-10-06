#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n, a, b, c;
    cin>>a>>b>>c>>n;
    vector<vector<ll>> dp(n + 2, vector<ll>(n + 2, LLMAX)); //dp[i][i + j - 1] => i -> start index, j -> range size
    for(int i = 0 ; i <= n + 1 ; i++){
        dp[i][0] = 0;
        dp[0][i] = 0;
        dp[i][i] = 0;
        if(i > 0) dp[i][i - 1] = 0;
    }
    for(int j = 2 ; j <= n ; j++){
        for(int i = 1 ; i <= n ; i++){
            for(int k = i ; k <= i + j - 1 ; k++){
                if(i + j - 1 > n) break;
                dp[i][i + j - 1] = min(dp[i][i + j - 1], max(dp[i][k - 1], dp[k + 1][i + j - 1]) + (a*(k-1)*(k-1) + b*(k-1) + c));
            }
        }
    }
    cout<<dp[1][n]<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision
    ll testCaseCount = 1;
    cin>>testCaseCount; //for test cases

    while(testCaseCount--) solve();
    return 0;
}
