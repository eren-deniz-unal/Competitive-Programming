#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

vector<ll> arr;
vector<ll> freq;
vector<ll> ans;
vector<vector<vector<ll>>> splitQueries; //{l, r, index}
map<ll, ll> compress;

void solve(){
    ll n, q;
    cin>>n>>q;
    ll sqrtN = sqrt(n) + 1;
    arr.resize(n);
    ans.resize(n);
    freq.resize(n);
    splitQueries.resize((n / sqrtN) + 5);
    
    for(int i = 0 ; i < n ; i++){
        cin>>arr[i];
    }
    for(int i = 0 ; i < n ; i++){
        ll l, r;
        cin>>l>>r;
        splitQueries[r/sqrtN].push_back({l-1, r-1, i});
    }

    vector<ll> compArr = arr;
    sort(compArr.begin(), compArr.end());
    compArr.erase(unique(compArr.begin(), compArr.end()), compArr.end());
    for(int i = 0 ; i < compArr.size() ; i++){
        compress[compArr[i]] = i;
    }
    for(int i = 0 ; i < sqrtN ; i++){
        sort(splitQueries[i].begin(), splitQueries[i].end());
    }

    ll curL = 0, curR = 0;
    freq[compress[arr[0]]]++;
    for(int i = 0 ; i < splitQueries.size() ; i++){
        for(int j = 0 ; j < splitQueries[i].size() ; j++){
            ll tarL = splitQueries[i][j][0];
            ll tarR = splitQueries[i][j][1];
            ll curAns = 0;

            while(curL < tarL){
                freq[compress[arr[curL]]]--;
                curL++;
            }
            while(curL > tarL){
                curL--;
                freq[compress[arr[curL]]]++;
            }
            
            while(curR < tarR){
                curR++;
                freq[compress[arr[curR]]]++;
            }
            while(curR > tarR){
                freq[compress[arr[curR]]]--;
                curR--;
            }

            ll curRealIndex = 0;
            ll k;
            for(k = 0 ; k < freq.size() ; k++){
                curRealIndex += freq[k];
                if(curRealIndex >= ((curR-curL+2) / 2)){
                    break;
                }
            }
            curAns = compArr[k];

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
