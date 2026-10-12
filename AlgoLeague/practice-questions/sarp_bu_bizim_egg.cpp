#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

const ll maxN = 1505;
ll dp[maxN][4]; //i -> floors left, j -> eggs left

void preCompute(){
    dp[0][0] = -1;
    dp[0][1] = 0;
    dp[0][2] = 0;
    dp[0][3] = 0;
    for(int i = 1 ; i < maxN ; i++){
        dp[i][0] = -1;
        dp[i][1] = dp[i-1][1] + 1;
        dp[i][2] = LLMAX;
        dp[i][3] = LLMAX;
    }
    dp[1][2] = 1;
    dp[1][3] = 1;
    for(int i = 2 ; i < maxN ; i++){
        for(int j = 1 ; j <= i ; j++){
            dp[i][2] = min(dp[i][2], max(dp[i-j][2], dp[j][1]) + 1);
            dp[i][3] = min(dp[i][3], max(dp[i-j][3], dp[j][2]) + 1);
        }
    }
}

void solve(){
    ll n;
    cin>>n;
    cout<<dp[n+1][3] - 1<<endl;
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
