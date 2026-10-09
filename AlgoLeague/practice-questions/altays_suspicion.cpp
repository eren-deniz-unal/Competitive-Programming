#include<bits/stdc++.h>
using namespace std;

#define ll int
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = 998243453;

const ll maxN = (3e7) + 5;
ll dp[maxN + 1];
ll ans[maxN + 1];

void preCompute(){
    dp[0] = 0;
    dp[1] = 1;
    ans[0] = 0;
    ans[1] = 1;
    for(int i = 2 ; i <= maxN ; i++){
        ll k = mod / i, r = mod % i;
        dp[i] = -(((long long)k * (long long)dp[r]) % mod);
        while(dp[i] < 0) dp[i] += mod;
    }
    for(int i = 2 ; i <= maxN ; i++){
        ans[i] = (((((long long)ans[i - 1] * (long long)i) % mod) * (long long)dp[i-1]) + 1) % mod;
    }
}

void solve(){
    //got hint from gemini -> to write it as m = k*n + r and to go for r^-1 in addition to n^-1
    ll n;
    cin>>n;
    cout<<ans[n]<<endl;
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
