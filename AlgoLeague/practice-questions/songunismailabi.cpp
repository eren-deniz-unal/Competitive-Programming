#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n, ans = 0;
    cin>>n;
    vector<ll> arr(n);
    vector<vector<bool>> isCoprime(260, vector<bool>(260, true));
    vector<ll> freq(260, 0);
    vector<ll> count(260, 0);

    for(int i = 2 ; i < 257 ; i++){
        if(isCoprime[i][i]){
            for(int j = i ; j < 257 ; j += i){
                for(int k = i ; k < 257 ; k += i){
                    isCoprime[j][k] = false;
                }
            }
        }
    }
    for(int i = 0 ; i < n ; i++){
        cin>>arr[i];
        freq[arr[i]]++;
        for(int j = 1 ; j < 257 ; j++){
            if(isCoprime[arr[i]][j]){
                ans += count[j];
            }
            count[j] += freq[j];
        }
    }
    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision
    ll testCaseCount = 1;
    //cin>>testCaseCount; //for test cases

    while(testCaseCount--) solve();
    return 0;
}
