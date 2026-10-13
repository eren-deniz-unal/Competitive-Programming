#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

void solve(){
    // its at max n sqrtn because at max unique counts becomes sum(i=0 -> x, (1/i) * i) and sum of all numbers smaller than x is equal to n so (x^2+x)/2=n => x=sqrtn ish
    ll n, q;
    cin>>n>>q;
    vector<ll> arr(n);
    vector<ll> ans(q);
    vector<vector<ll>> queries(q, vector<ll>(5, 0)); //{k, LmodK, l, r, index}
    vector<ll> curPreSum(n);
    for(int i = 0 ; i < n ; i++){
        cin>>arr[i];
    }
    for(int i = 0 ; i < q ; i++){
        cin>>queries[i][2]>>queries[i][3]>>queries[i][0];
        queries[i][2]--;
        queries[i][3]--;
        queries[i][1] = queries[i][2] % queries[i][0];
        queries[i][4] = i;
    }

    sort(queries.begin(), queries.end());

    ll lastK = -1, lastLmodK = -1;
    for(int curQ = 0 ; curQ < q ; curQ++){
        ll k = queries[curQ][0], LmodK = queries[curQ][1], l = queries[curQ][2], r = queries[curQ][3], curIndex = queries[curQ][4];
        if(lastK != k || lastLmodK != LmodK){
            curPreSum[0] = arr[LmodK];
            for(int i = 1 ; i < ((n - LmodK - 1) / k) + 1 ; i++){
                curPreSum[i] = curPreSum[i - 1] + arr[LmodK + (k * i)];
            }
        }
        l /= k;
        r = (r - LmodK) / k;
        ans[curIndex] = curPreSum[r] - (l == 0 ? 0 : curPreSum[l - 1]);
        lastK = k; lastLmodK = LmodK;
    }

    for(int i = 0 ; i < q ; i++){
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
