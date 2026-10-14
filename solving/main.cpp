#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    ll n, q;
    cin>>n>>q;
    ll sqrtN = sqrt(n) + 1;
    vector<ll> arr(n);
    vector<ll> ans(n);
    vector<vector<vector<ll>>> splitQueries(sqrtN); //{l, r, index}
    arr[0] = -1;
    for(int i = 0 ; i < n ; i++){
        cin>>arr[i];
    }
    for(int i = 0 ; i < n ; i++){
        ll l, r;
        cin>>l>>r;
        splitQueries[r/sqrtN].push_back({l, r, i});
    }
    for(int i = 0 ; i < sqrtN ; i++){
        sort(splitQueries.begin(), splitQueries.end());
    }
    ll curL, curR;
    for(int i = 0 ; i < sqrtN ; i++){
        for(int j = 0 ; j < splitQueries[i].size() ; j++){
            ll tarL = splitQueries[i][j][0];
            ll tarR = splitQueries[i][j][1];
            ll curAns = 0;

            //go to tarL and tarR

            ans[splitQueries[i][j][2]] = curAns;
        }
    }
    for(int i = 0 ; i < n ; i++){
        cout<<ans[i]<<endl;
    }
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
