#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

ll segTree[int(8e5) + 5];
ll dp[int(2e5) + 5];

void initialize(ll curIndex, ll curL, ll curR){
    if(curR == curL){
        segTree[curIndex] = 0;
        return;
    }
    ll mid = (curL + curR) / 2;
    initialize(curIndex * 2, curL, mid);
    initialize(curIndex * 2 + 1, mid + 1, curR);
    segTree[curIndex] = 0;
}

void update(ll tarL, ll tarR, ll tarVal, ll curIndex, ll curL, ll curR){
    if(curR < tarL || curL > tarR){
        return;
    }
    if(curR <= tarR && curL >= tarL){
        if(dp[segTree[curIndex]] < dp[tarVal]) segTree[curIndex] = tarVal;
        return;
    }
    ll mid = (curL + curR) / 2;
    update(tarL, tarR, tarVal, curIndex * 2, curL, mid);
    update(tarL, tarR, tarVal, curIndex * 2 + 1, mid + 1, curR);
}

ll querry(ll tarIndex, ll curIndex, ll curL, ll curR){
    if(curL == curR && curL == tarIndex){
        return segTree[curIndex];
    }
    if(curR < tarIndex || curL > tarIndex) return 0;
    ll mid = (curL + curR) / 2;

    if(tarIndex <= mid){
        ll newVal = querry(tarIndex, curIndex * 2, curL, mid);
        if(dp[newVal] < dp[segTree[curIndex]]) return segTree[curIndex];
        else return newVal;
    }
    else{
        ll newVal = querry(tarIndex, curIndex * 2 + 1, mid + 1, curR);
        if(dp[newVal] < dp[segTree[curIndex]]) return segTree[curIndex];
        else return newVal;
    }
}

void solve(){
    ll n;
    cin>>n;
    ll segN = (2 << int(log2(n)));
    ll h[n + 1];
    ll arr[n + 1];
    dp[0] = 0;
    for(int i = 1 ; i <= n ; i++){
        cin>>h[i];
        dp[i] = 0;
    }
    for(int i = 1 ; i <= n ; i++){
        cin>>arr[i];
    }

    ll ans = 0;
    initialize(1, 1, segN);
    for(int i = 1 ; i <= n ; i++){
        dp[h[i]] = dp[querry(h[i], 1, 1, segN)] + arr[i]; //segTree with range updates
        update(h[i], n + 1, h[i], 1, 1, segN); //why n + 1 (n makes the last dp wrong, segN make lower numbers include higher ones)?
        ans = max(ans, dp[h[i]]);
    }

    cout<<ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(numeric_limits<double>::max_digits10); // set cout to print up to 10 digits of precision

    solve();
    
    return 0;
}
