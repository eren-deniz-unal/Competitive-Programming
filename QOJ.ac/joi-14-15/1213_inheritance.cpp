#include<bits/stdc++.h>
using namespace std;

#define ll int
#define endl '\n'
#define LLMAX LONG_LONG_MAX
#define LLMIN LONG_LONG_MIN
const ll mod = (1e9) + 7;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rngNum(ll l, ll r){ return uniform_int_distribution<ll>(l, r)(rng); }

ll n, m, k;
vector<array<ll, 4>> edgeList; //{weight node1, node2, index}
vector<vector<ll>> dsu;
vector<vector<ll>> dsuSize;
vector<ll> ans;

ll dsuFind(ll whichDsu, ll node){
    ll init = node;
    while(node != dsu[whichDsu][node]){
        node = dsu[whichDsu][node];
    }
    ll temp;
    while(init != node){
        temp = dsu[whichDsu][init];
        dsu[whichDsu][init] = node;
        init = temp;
    }
    return node;
}

void dsuMerge(ll whichDsu, ll node1, ll node2){
    node1 = dsuFind(whichDsu, node1);
    node2 = dsuFind(whichDsu, node2);
    if(dsuSize[whichDsu][node1] < dsuSize[whichDsu][node2]){
        dsuSize[whichDsu][node1] = 0;
        dsuSize[whichDsu][node2]++;
        dsu[whichDsu][node1] = node2;
    }
    else{
        dsuSize[whichDsu][node2] = 0;
        dsuSize[whichDsu][node1]++;
        dsu[whichDsu][node2] = node1;
    }
}

bool dsuCheck(ll whichDsu, ll node1, ll node2){
    node1 = dsuFind(whichDsu, node1);
    node2 = dsuFind(whichDsu, node2);
    return node1 == node2;
}

void solve(){
    cin>>n>>m>>k;
    ans.resize(m);
    edgeList.resize(m);
    for(int i = 0 ; i < m ; i++){
        ll a, b, c;
        cin>>a>>b>>c;
        edgeList[i] = {c, --a, --b, i};
    }
    sort(edgeList.begin(), edgeList.end());
    reverse(edgeList.begin(), edgeList.end());
    dsu.resize(k+1, vector<ll>(n));
    dsuSize.resize(k+1, vector<ll>(n, 1));
    for(int i = 0 ; i < k ; i++){
        for(int j = 0 ; j < n ; j++){
            dsu[i][j] = j;
        }
    }
    for(auto e : edgeList){
        ll node1 = e[1];
        ll node2 = e[2];
        ll index = e[3];
        ll l = 0, r = k;
        while(l < r){
            ll mid = (l+r)/2;
            if(dsuCheck(mid, node1, node2)){
                l = mid + 1;
            }
            else{
                r = mid;
            }
        }

        if(l != k){
            dsuMerge(l, node1, node2);
            ans[index] = l+1;
        }
    }
    for(int i = 0 ; i < m ; i++){
        cout<<ans[i]<<endl;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<fixed<<setprecision(10); // set cout to print up to 10 digits of precision

    if(fopen("walk.in", "r")){
        freopen("walk.in", "r", stdin);
        freopen("walk.out", "w", stdout);
    } //for usaco site

    ll testCaseCount = 1;
    //cin>>testCaseCount; //for test cases

    while(testCaseCount--) solve();
    return 0;
}
