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
    ll oneCount = 0, twoCount = 0, threeCount = 0;
    
    for(int i = 1 ; i <= n ; i++){
        cin>>arr[i];
        if(arr[i] == 1) oneCount++;
        if(arr[i] == 2) twoCount++;
        if(arr[i] == 3) threeCount++;
    }
    //seg fault at n = 300
    ll dp[n + 1][n + 1][n + 1]; // dp[i][j][k] => i -> 1 count, j -> 2 count, k -> 3 count
    dp[0][0][0] = 0;

    for(int k = 0 ; k <= n ; k++){
        for(int j = 0 ; j <= n ; j++){
            for(int i = 0 ; i <= n ; i++){
                if(i == 0 && j == 0 && k == 0) continue;
                dp[i][j][k] = (i != 0 ? dp[i - 1][j][k] * i : 0);
                dp[i][j][k] += (j != 0 ? dp[i + 1][j - 1][k] * j : 0);
                dp[i][j][k] += (k != 0 ? dp[i][j + 1][k - 1] * k : 0);
                dp[i][j][k] /= double(i + j + k);
                dp[i][j][k] += (double(n) / double(i + j + k));
            }
        }
    }

    cout<<dp[oneCount][twoCount][threeCount];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(numeric_limits<double>::max_digits10);

    solve();

    return 0;
}
