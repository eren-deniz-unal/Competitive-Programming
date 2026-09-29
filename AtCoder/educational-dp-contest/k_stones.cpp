#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n, k;
    cin>>n>>k;
    ll arr[n];
    for(int i = 0 ; i < n ; i++){
        cin>>arr[i];
    }

    bool dp[k + 1][2]; //dp[i][j] => i -> how tall the pile is, j -> whose move is it, dp[i][j] = who wins with optimal play (false -> first, true -> second)
    dp[0][0] = true;
    dp[0][1] = false;

    for(int i = 1 ; i <= k ; i++){
        dp[i][0] = true;
        dp[i][1] = false;
        for(int j = 0 ; j < n ; j++){
            if(i >= arr[j] && !dp[i - arr[j]][1]){
                dp[i][0] = false;
                break;
            }
        }
        for(int j = 0 ; j < n ; j++){
            if(i >= arr[j] && dp[i - arr[j]][0]){
                dp[i][1] = true;
                break;
            }
        }
    }

    if(dp[k][0]){
        cout<<"Second";
    }
    else{
        cout<<"First";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(numeric_limits<double>::max_digits10);

    solve();

    return 0;
}
