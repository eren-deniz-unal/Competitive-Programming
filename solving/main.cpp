#include<bits/stdc++.h>
using namespace std;

#define ll int
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    // its at max n sqrtn because at max unique counts becomes sum(i=0 -> x, (1/i) * i) and sum of all numbers smaller than x is equal to n so (x^2+x)/2=n => x=sqrtn ish
    ll n, q;
    cin>>n>>q;
    vector<ll> arr(n);
    vector<vector<bool>> ansDone(n + 1); //[k][l % k] -> k jumps and start from l % k
    vector<vector<vector<ll>>> ansPresums(n + 1); //[k][l] -> k jumps and end at l (define it as [k][l][i] => k -> k jumps, l -> start at l, i -> cur index)
    for(int i = 0 ; i < n ; i++){
        cin>>arr[i];
    }
    while(q--){
        ll l, r, k;
        cin>>l>>r>>k;
        l--; r--;
        ll LmodK = l % k;
        if(ansDone[k].size() == 0){
            ansDone[k] = (vector<bool>(k, false));
            ansPresums[k] = (vector<vector<ll>>(LmodK));
        }
        if(!ansDone[k][LmodK]){
            ansPresums[k][LmodK][0] = arr[LmodK];
            for(int i = 0 ; i < n / k ; i++){
                ansPresums[k][LmodK][i] = ansPresums[k][LmodK][i - 1] + arr[i];
            }
            ansDone[k][LmodK] = true;
        }
        cout<<(ansPresums[k][LmodK][r / k] - (l/k > 0 ? ansPresums[k][LmodK][l/k - 1] : 0))<<endl;
        //bugtest (keep memory in mind)
        //if it doesnt work maybe get all queries and solve offline where while calculating for k + LmodK you calculate like a presum but only keep the ans for all the [l-1] and [r]'s for each (k, LmodK) pair you calculate
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
