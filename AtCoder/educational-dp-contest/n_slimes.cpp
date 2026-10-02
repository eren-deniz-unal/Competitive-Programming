#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll dpCut[405][405][405]; //dp[i][j][k] => i -> left index, j -> range size, k -> cut location

void solve(){
    //took a lot of time to find the solution
    //also looked at it on paper and took like 2-3ish hours to find the logic (after a naiver try)
    //took around 1-1.5 hours to code and debug
    ll n;
    cin>>n;
    ll arr[n + 1];
    ll preSum[n + 1];
    ll dpChoose[n + 1][n + 1]; //dp[i][j][k] => i -> left index, j -> range size
    preSum[0] = 0;
    for(int i = 1 ; i <= n ; i++){
        cin>>arr[i];
        dpCut[i][0][0] = 0;
        dpCut[0][i][0] = 0;
        dpCut[0][0][i] = 0;
        dpChoose[i][0] = 0;
        dpChoose[0][i] = 0;
        dpChoose[i][1] = 0;
        preSum[i] = preSum[i - 1] + arr[i];
    }
    dpCut[0][0][0] = 0;
    dpChoose[0][0] = 0;

    for(int j = 2 ; j <= n ; j++){
        for(int i = 1 ; i <= n - j + 1 ; i++){
            dpChoose[i][j] = LLMAX;
            for(int k = i ; k < i + j - 1 && k < n ; k++){
                dpCut[i][j][k] = dpChoose[i][k - i + 1] + dpChoose[k + 1][i + j - k - 1];
                dpChoose[i][j] = min(dpChoose[i][j], dpCut[i][j][k] + (preSum[k] - preSum[i - 1]) + (preSum[i + j - 1] - preSum[k]));
            }
        }
    }
    cout<<dpChoose[1][n];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(numeric_limits<double>::max_digits10); // set cout to print up to 10 digits of precision

    solve();

    return 0;
}
