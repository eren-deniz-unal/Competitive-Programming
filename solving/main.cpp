#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

vector<ll> arr;
vector<ll> compArr;
vector<ll> ans;
vector<vector<vector<ll>>> splitQueries; //{l, r, index}
map<ll, ll> freq;

void solve(){
    ll n, q;
    cin>>n>>q;
    ll sqrtN = sqrt(n) + 1;
    arr.resize(n);
    ans.resize(n);
    splitQueries.resize((n / sqrtN) + 5);
    
    for(int i = 0 ; i < n ; i++){
        cin>>arr[i];
    }
    for(int i = 0 ; i < n ; i++){
        ll l, r;
        cin>>l>>r;
        splitQueries[r/sqrtN].push_back({l-1, r-1, i});
    }

    compArr = arr;
    unique_copy(arr.begin(), arr.end(), compArr.begin());
    sort(compArr.begin(), compArr.end());
    for(int i = 0 ; i < sqrtN ; i++){
        sort(splitQueries[i].begin(), splitQueries[i].end());
    }

    ll curL = 0, curR = 0;
    freq[arr[0]]++;
    for(int i = 0 ; i < splitQueries.size() ; i++){
        for(int j = 0 ; j < splitQueries[i].size() ; j++){
            ll tarL = splitQueries[i][j][0];
            ll tarR = splitQueries[i][j][1];
            ll curAns = 0;

            while(curL < tarL){
                compArr[arr[curL]]--;
                curL++;
            }
            while(curL > tarL){
                curL--;
                compArr[arr[curL]]++;
            }
            
            while(curR < tarR){
                curR++;
                compArr[arr[curR]]++;
            }
            while(curR > tarR){
                compArr[arr[curR]]--;
                curR--;
            }

            ll curRealIndex = 0;
            for(int i = 0 ; i < freq.size() ; i++){
                curRealIndex += freq[i];
                if(curRealIndex >= ((curR-curL+2) / 2)){
                    break;
                }
            }
            curAns = arr[curRealIndex];

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
