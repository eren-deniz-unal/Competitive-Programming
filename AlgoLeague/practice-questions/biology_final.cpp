#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = 998244353;

const ll maxN = (5e3) + 5;
ll dp[maxN + 1][maxN + 1];

void preCompute(){
    ll curFac = 1;
    dp[0][0] = 1;
    dp[1][0] = 0;
    for(int i = 2 ; i < maxN ; i++){
        (dp[i][0] = dp[i-1][0] * i + (i % 2 == 0 ? 1 : -1)) %= mod;
    }
    for(int j = 1 ; j <= maxN ; j++){
        if(j != 0) (curFac *= j) %= mod;
        for(int i = 0 ; i <= maxN ; i++){
            dp[i][j] = 0;
            if(2*j == i) dp[i][j] = (curFac * curFac) % mod;
        }
    }
    dp[2][1] = 1;
    dp[3][1] = 2;
    for(int i = 4 ; i <= maxN ; i++){
        for(int j = 1 ; j <= maxN ; j++){
            if(2*j < i) dp[i][j] = (((dp[i-1][j-1] * ((i-1) - 2*(j-1))) % mod) + ((dp[i-2][j-1] * ((i-1) - (j-1))) % mod)) % mod;
        }
    }
}

void solve(){
    ll n, m;
    cin>>n>>m;
    cout<<dp[n][m]<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision
    ll testCaseCount = 1;
    cin>>testCaseCount; //for test cases
    preCompute();

    while(testCaseCount--) solve();
    return 0;
}
